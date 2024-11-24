import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from copy import deepcopy

from collections import deque

def reward_fn_wrapper(state, action, reward, next_state, done):
    left_range = 0.45
    right_range = 0.57
    if state[0] <= left_range and next_state[0] < state[0]:
        reward = -1
    elif state[0] >= right_range and next_state[0] > state[0]:
        reward = -1
    else:
        reward = 2
    
    if abs(state[2]) < abs(next_state[2]):
        reward = -1
    
    return reward

class ReplayBuffer:
    '''
    saves transition datas to buffer
    '''

    def __init__(self, buffer_size=100000, n_step=1, gamma=0.85):
        '''
        Replay Buffer initialize function

        args:
            buffer_size: maximum size of buffer
            n_step: n step if using n step DQN
            gamma: discount factor for n step
        '''
        self.buffer_size = buffer_size
        self.n_step = n_step
        self.gamma = gamma
        
        self.states = deque(maxlen=buffer_size)
        self.actions = deque(maxlen=buffer_size)
        self.rewards = deque(maxlen=buffer_size)
        self.next_states = deque(maxlen=buffer_size)
        self.dones = deque(maxlen=buffer_size)

        self.n_states = deque(maxlen=self.n_step)
        self.n_actions = deque(maxlen=self.n_step)
        self.n_rewards = deque(maxlen=self.n_step)
        self.n_next_states = deque(maxlen=self.n_step)
        self.n_dones = deque(maxlen=self.n_step)


    def __len__(self) -> int:
        return len(self.states)


    def add(self, state, action, reward, next_state, done):
        '''
        add sample to the buffer
        '''

        reward = reward_fn_wrapper(state, action, reward, next_state, done)
        if self.n_step > 1:
            self.n_states.append(state)
            self.n_actions.append(action)
            self.n_rewards.append(reward)
            self.n_next_states.append(next_state)
            self.n_dones.append(done)
            
            if len(self.n_states) == self.n_step:
                n_reward = 0
                for i in range(self.n_step):
                    n_reward += self.n_rewards[i] * (self.gamma ** i)
                
                self.states.append(self.n_states[0])
                self.actions.append(self.n_actions[0])
                self.rewards.append(n_reward)
                self.next_states.append(self.n_next_states[0])
                self.dones.append(self.n_dones[0])
        else:
            self.states.append(state)
            self.actions.append(action)
            self.rewards.append(reward)
            self.next_states.append(next_state)
            self.dones.append(done)

    
    def sample(self, batch_size, device=None):
        '''
        samples random batches from buffer

        args:
            batch_size: size of the minibatch
            device: pytorch device

        returns:
            states, actions, rewards, next_states, dones
        '''
        indices = np.random.choice(len(self), batch_size, replace=False)

        sp_states = torch.tensor(np.array([self.states[i] for i in indices]), dtype=torch.float32, device=device)
        sp_actions = torch.tensor(np.array([self.actions[i] for i in indices]), dtype=torch.int64, device=device)
        sp_rewards = torch.tensor(np.array([self.rewards[i] for i in indices]), dtype=torch.float32, device=device)
        sp_next_states = torch.tensor(np.array([self.next_states[i] for i in indices]), dtype=torch.float32, device=device)
        sp_dones = torch.tensor(np.array([self.dones[i] for i in indices]), dtype=torch.float32, device=device)

        return sp_states, sp_actions, sp_rewards, sp_next_states, sp_dones
    

class DQN(nn.Module):
    '''
    Pytorch module for Deep Q Network
    '''
    def __init__(self, input_size, output_size):
        '''
        Define your architecture here
        '''
        super().__init__()
        
        hidden_size = 128
        self.lin1 = nn.Linear(input_size, hidden_size)
        self.lin2 = nn.Linear(hidden_size, hidden_size)
        self.lin3 = nn.Linear(hidden_size, output_size)
       
    def forward(self, state):
        '''
        Get Q values for each action given state
        '''
        q = F.relu(self.lin1(state))
        q = F.relu(self.lin2(q))
        q = self.lin3(q)
        return q


class Agent:
    def __init__(self, state_size, action_size):

        # environment parameters
        self.curr_step = 0
        self.state_size = state_size
        self.action_size = action_size

        # hyperparameters
        self.learning_rate = 0.0005 # initial 0.0003
        self.batch_size = 128 # initial 64
        self.gamma = 0.85
        self.epsilon = 0.5
        self.epsilon_decay = 0.99
        self.n_step = 1 # 1 is normal DQN, over 1 is n-step DQN

        # related to pytorch
        self.device = torch.device('cpu')
        # self.device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
        
        self.network = DQN(state_size, action_size).to(self.device)
        self.target_network = deepcopy(self.network)
        self.optimizer = torch.optim.Adam(params=self.network.parameters(), lr=self.learning_rate)
        self.loss_fn = nn.MSELoss()

        # related to replay buffer
        self.buffer_size = 50000
        self.replay_buffer = ReplayBuffer(buffer_size=self.buffer_size, n_step=self.n_step, gamma=self.gamma)

        # related to update
        self.target_update_freq = 300
        self.gradient_update_freq = 10
        self.epsilon_decay_freq = 100

    def select_action(self, state, is_test=False):
        '''
        selects action given state

        returns:
            discrete action integer
        '''
        if is_test:
            return self.network(torch.tensor(state, dtype=torch.float32, device=self.device)).argmax().item()
        
        if np.random.rand() < self.epsilon:
            return np.random.randint(self.action_size)
        else:
            return self.network(torch.tensor(state, dtype=torch.float32, device=self.device)).argmax().item()

    def train_network(self, states, actions, rewards, next_states, dones):
        states = states.reshape(-1, self.state_size)
        next_states = next_states.reshape(-1, self.state_size)

        q_values = self.network(states).gather(1, actions.unsqueeze(1)).squeeze(1)

        next_q_values = self.target_network(next_states).max(dim=1).values
        target_q_values = rewards + (self.gamma ** self.n_step)* next_q_values * (1 - dones)

        loss = self.loss_fn(q_values, target_q_values)

        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

    def update_target_network(self):
        '''
        updates the target network to online
        '''
        # Use deepcopy of online network
        del self.target_network
        self.target_network = deepcopy(self.network)

    def step(self, state, action, reward, next_state, done):
        self.curr_step += 1
        self.replay_buffer.add(state, action, reward, next_state, done)

        if self.curr_step % self.gradient_update_freq == 0 and len(self.replay_buffer) > self.batch_size:
            self.train_network(*self.replay_buffer.sample(self.batch_size, device=self.device))
        
        if self.curr_step % self.target_update_freq == 0:
            self.update_target_network()
        
        if self.curr_step % self.epsilon_decay_freq == 0:
            self.epsilon *= self.epsilon_decay
        
        if self.curr_step == 40000:
            self.learning_rate = 0.0003
            self.optimizer = torch.optim.Adam(params=self.network.parameters(), lr=self.learning_rate)