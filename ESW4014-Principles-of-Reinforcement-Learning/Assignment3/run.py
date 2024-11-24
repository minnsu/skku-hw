import warnings
# warnings.filterwarnings("ignore")
import numpy as np
import torch.multiprocessing as mp
from torch.distributions import Normal
from collections import deque
import torch
import time
import gym
from agent import Worker, ActorCritic
import matplotlib.pyplot as plt

def visualize_env(agent=None):
    env = gym.make('InvertedPendulumSwingupBulletEnv-v0')
    env.seed(1)
    env.action_space.seed(1)
    env.render(mode='human')
    state = env.reset()
    total_rewards = 0

    for step in range(200):
        time.sleep(0.016)
        if agent is None:
            action = env.action_space.sample()
        else:
            action = agent.select_action(state)
        next_state, reward, done, _ = env.step(action)

        print("reward:", reward)
        total_rewards = total_rewards + reward
        if done:
            print("total reward:", total_rewards)
            total_rewards = 0
            state = env.reset()
        state = next_state

def evaluate(global_actor, global_epi, sync, finish, multi):
    start_time = time.time()
    env = gym.make('InvertedPendulumSwingupBulletEnv-v0')
    env.seed(1)
    recent_scores = deque(maxlen=20)
    mean_scores = []
    n_epi = 0

    while True:
        # Worker들의 에피소드 카운트가 병렬 프로세스의 개수와 같아지면(각각 한 에피소드씩 끝나면) global actor로 evaluation 
        if global_epi.value == multi:
            state = env.reset()        
            score = 0
            done = False

            while not done:
                with torch.no_grad():
                    mu, std = global_actor.actor(torch.FloatTensor(state))
                    dist = Normal(mu, std)
                    action = dist.sample()
                    next_state, reward, done, _ = env.step(action)
                    state = next_state
                    score += reward

            # 한 에피소드 evaluation이 끝나면 대기 중인 Worker process들을 모두 재시작            
            with sync:
                sync.notify_all()

            # Worker의 에피소드 카운트 초기화
            with global_epi.get_lock():
                global_epi.value = 0

            recent_scores.append(score)
            mean_score = np.mean(recent_scores)
            mean_scores.append(mean_score)
            n_epi += 1
            print(f'[Episode {n_epi}] Avg. score: {mean_score: .2f}')

            if mean_score >= 600:
                with finish.get_lock():
                    finish.value = 1
                print("Achieved score 600!!!, Time : {:.2f}".format(time.time() - start_time))
            elif n_epi > 1000:
                with finish.get_lock():
                    finish.value = 1
                if np.max(mean_scores) >= 500:
                    print("Max episode finished! Achieved score 500!!!")
                elif np.max(mean_scores) >= 400:
                    print("Max episode finished! Achievd score 400!!!")
                else:
                    print("Max episode finished!")

            # 학습 종료
            if finish.value == 1:
                with sync:
                    sync.notify_all()
                break

    plt.figure()
    plt.plot(np.arange(len(mean_scores)), mean_scores)
    plt.axhline(400, linestyle='--')
    plt.axhline(500, linestyle='--')
    plt.axhline(600, linestyle='--')
    plt.xlabel('Episode')
    plt.ylabel('Mean Score')
    plt.savefig('plot.png')
    plt.close()
    print('figure saved')  

    env.close()

def model_free_RL(n_steps, multi):
    # Global actor 선언 
    global_actor = ActorCritic()
    global_actor.share_memory()

    # Global - local worker 간 공유되는 에피소드 카운트, 대기 조건, 학습 종료 조건 선언
    global_epi = mp.Value('i', 0)
    sync = mp.Condition()
    finish = mp.Value('i', 0)

    # Multiprocessing
    processes = []

    for rank in range(multi + 1):
        # Global actor의 evaluation
        if rank == 0:
            p = mp.Process(target=evaluate, args=(global_actor, global_epi, sync, finish, multi))
            p.start()

        # Local worker의 learning
        else:
            worker = Worker(global_actor, global_epi, sync, finish, n_steps, rank)
            p = mp.Process(target=worker.train)
            p.start()
            processes.append(p)

    for p in processes:
        p.join()

    return worker

if __name__ == '__main__':
    while True:
        print("1. visualize without learning")
        print("2. actor-critic training")
        print("3. visualize after learning")
        print("4. exit")
        menu = int(input("select: "))
        if menu == 1:
            visualize_env()
        elif menu == 2:
            n_steps = int(input("n_steps: "))
            multi = int(input("multi: ")) 
            torch.manual_seed(77)
            np.random.seed(1)
            agent = model_free_RL(n_steps, multi)
        elif menu == 3:
            visualize_env(agent)
        elif menu == 4:
            break
        else:
            print("wrong input!")
