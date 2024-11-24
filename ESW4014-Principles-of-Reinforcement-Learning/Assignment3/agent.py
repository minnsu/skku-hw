import gym
import pybullet_envs
import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.distributions import Normal

import numpy as np

ENV = gym.make("InvertedPendulumSwingupBulletEnv-v0")
OBS_DIM = ENV.observation_space.shape[0]
ACT_DIM = ENV.action_space.shape[0]
ACT_LIMIT = ENV.action_space.high[0]
ENV.close()

ENABLE_GRAD_CLIPPING = False
GRAD_CLIP_MAX_NORM = 1.0


#########################################################################################################################
############ 이 template에서는 DO NOT CHANGE 부분을 제외하고 마음대로 수정, 구현 하시면 됩니다                    ############
#########################################################################################################################

## 주의 : "InvertedPendulumSwingupBulletEnv-v0"은 continuious action space 입니다.
## Asynchronous Advantage Actor-Critic(A3C)를 참고하면 도움이 될 것 입니다.

 
class NstepBuffer:
    '''
    Save n-step trainsitions to buffer
    '''
    def __init__(self):
        self.states = []
        self.actions = []
        self.rewards = []
        self.next_states = []
        self.dones = []

    def add(self, state, action, reward, next_state, done):
        '''
        add sample to the buffer
        '''
        self.states.append(state)
        self.actions.append(action)
        self.rewards.append(reward)
        self.next_states.append(next_state)
        self.dones.append(done)

    def sample(self):
        '''
        sample transitions from buffer
        '''
        return self.states, self.actions, self.rewards, self.next_states, self.dones
    
    def reset(self):
        '''
        reset buffer
        '''
        self.states = []
        self.actions = []
        self.rewards = []
        self.next_states = []
        self.dones = []


class ActorCritic(nn.Module):
    '''
    Pytorch module for Actor-Critic network
    '''
    def __init__(self):
        '''
        Define your architecture here
        '''
        super(ActorCritic, self).__init__()

        self._actor = nn.Sequential(
            nn.Linear(OBS_DIM, 256),
            nn.ReLU(),
        )
        self._actor_mu = nn.Linear(256, ACT_DIM)
        self._actor_std = nn.Linear(256, ACT_DIM)

        self._critic = nn.Sequential(
            nn.Linear(OBS_DIM + ACT_DIM, 128),
            nn.Tanh(),
            nn.Linear(128, 1)
        )

    def actor(self, states):
        '''
        Get action distribution (mean, std) for given states
        '''
        states = torch.tensor(np.array(states), dtype=torch.float32)

        x = self._actor(states)
        mu = self._actor_mu(x)
        std = self._actor_std(x)
        std = torch.clamp(std, 1e-6, 1)

        return mu, std

    def critic(self, states, actions):
        '''
        Get values for given states
        '''
        states = torch.tensor(np.array(states), dtype=torch.float32)
        actions = torch.tensor(np.array(actions), dtype=torch.float32)
        inputs = torch.cat([states, actions], dim=-1)
        return self._critic(inputs)


class Worker(object):
    def __init__(self, global_actor, global_epi, sync, finish, n_step, seed):
        self.env = gym.make('InvertedPendulumSwingupBulletEnv-v0')
        self.env.seed(seed)
        self.lr = 0.001
        self.gamma = 0.95
        self.entropy_coef = 0

        ############################################## DO NOT CHANGE ##############################################
        self.global_actor = global_actor
        self.global_epi = global_epi
        self.sync = sync
        self.finish = finish
        self.optimizer = optim.Adam(self.global_actor.parameters(), lr=self.lr)
        ###########################################################################################################  
        
        self.n_step = n_step
        self.local_actor = ActorCritic()
        self.nstep_buffer = NstepBuffer()

    def select_action(self, state):
        '''
        selects action given state

        return:
            continuous action value
        '''
        mean, std = self.local_actor.actor(state)
        dist = Normal(mean, std)
        return dist.sample().clamp(-ACT_LIMIT, ACT_LIMIT)
       
    def train_network(self, states, actions, rewards, next_states, dones):
        '''
        Advantage Actor-Critic training algorithm
        '''

        states = torch.tensor(np.array(states), dtype=torch.float32)
        actions = torch.tensor(actions, dtype=torch.float32).unsqueeze(-1)
        rewards = torch.tensor(rewards, dtype=torch.float32).unsqueeze(-1)
        next_states = torch.tensor(np.array(next_states), dtype=torch.float32)
        dones = torch.tensor(dones, dtype=torch.float32).unsqueeze(-1)

        # Compute return-to-go
        returns = torch.zeros_like(rewards)
        last_value = self.local_actor.critic(next_states[-1], actions[-1]).detach().item()
        R = last_value
        for t in reversed(range(len(rewards))):
            R = rewards[t] + self.gamma * R * (1 - dones[t])
            returns[t] = R

        # Compute critic loss
        values = self.local_actor.critic(states, actions)
        advantages = returns - values
        critic_loss = F.mse_loss(values, returns)

        # Compute actor loss
        mean, std = self.local_actor.actor(states)
        dist = Normal(mean, std)
        log_probs = dist.log_prob(actions)

        entropy = dist.entropy().mean()
        actor_loss = -(log_probs * advantages.detach()).mean() - self.entropy_coef * entropy

        total_loss = actor_loss + critic_loss
         
        ############################################## DO NOT CHANGE ##############################################
        # Global optimizer update 준비
        
        # Global Network와 Local Network의 모든 파라미터의 gradients를 0으로 초기화
        self.optimizer.zero_grad(set_to_none=False)
        
        total_loss.backward()

        # Gradient Clipping 관련 전역 변수가 정의되어 있는지 확인
        if 'ENABLE_GRAD_CLIPPING' in globals() and 'GRAD_CLIP_MAX_NORM' in globals():
            # 활성화 여부에 따라 Gradient Clipping 적용
            if ENABLE_GRAD_CLIPPING:
                torch.nn.utils.clip_grad_norm_(parameters=self.local_actor.parameters(), max_norm=GRAD_CLIP_MAX_NORM)

        # Local parameter를 global parameter로 전달
        for global_param, local_param in zip(self.global_actor.parameters(), self.local_actor.parameters()):
                global_param._grad = local_param.grad

        # Global optimizer update
        self.optimizer.step()

        # Global parameter를 local parameter로 전달
        self.local_actor.load_state_dict(self.global_actor.state_dict())
        ###########################################################################################################  

    def train(self):
        step = 1

        while True:
            state = self.env.reset()
            done = False

            while not done:
                action = self.select_action(state)
                next_state, reward, done, _ = self.env.step(action)
                self.nstep_buffer.add(state, action.item(), reward, next_state, done)

                # n step마다 한 번씩 train_network 함수 실행
                if step % self.n_step == 0 or done:
                    self.train_network(*self.nstep_buffer.sample())
                    self.nstep_buffer.reset()                    
                
                state = next_state
                step += 1

            ############################################## DO NOT CHANGE ##############################################
            # 에피소드 카운트 1 증가                
            with self.global_epi.get_lock():
                self.global_epi.value += 1
            
            # evaluation 종료 조건 달성 시 local process 종료
            if self.finish.value == 1:
                break

            # 매 에피소드마다 global actor의 evaluation이 끝날 때까지 대기 (evaluation 도중 파라미터 변화 방지)
            with self.sync:
                self.sync.wait()
            ###########################################################################################################

        self.env.close()
