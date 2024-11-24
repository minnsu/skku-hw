import gym
from collections import deque
import sys
from collections import defaultdict
import numpy as np
from agent import Agent
#from codes.agent_answer import Agent

env = gym.make('Taxi-v3')

action_size = env.action_space.n
print("Action Space", env.action_space.n)
print("State Space", env.observation_space.n)

def testing_without_learning():
    state = env.reset()
    total_rewards = 0

    def decode(i):
        out = []
        out.append(i % 4)
        i = i // 4
        out.append(i % 5)
        i = i // 5
        out.append(i % 5)
        i = i // 5
        out.append(i)
        return reversed(out)

    while True:
        env.render()
        print(list(decode(state)))
        print("0:down, 1:up, 2:right, 3:left, 4:pick, 5:dropoff")
        action = int(input("select action: "))
        while action not in [0,1,2,3,4,5]:
            action = int(input("select action: "))
        next_state, reward, done, _ = env.step(action)
        print("reward:", reward)
        total_rewards = total_rewards + reward
        if done:
            print("total reward:", total_rewards)
            break
        state = next_state



def model_free_RL(Q, mode):
    agent = Agent(Q, mode)
    num_episodes = 100000
    last_100_episode_rewards = deque(maxlen=100)
    for i_episode in range(1, num_episodes+1):

        state = env.reset()
        episode_rewards = 0

        while True:
            action = agent.select_action(state)
            next_state, reward, done, _ = env.step(action)
            agent.step(state, action, reward, next_state, done)

            episode_rewards += reward
            if done:
                last_100_episode_rewards.append(episode_rewards)
                break

            state = next_state

        if (i_episode >= 100):
            avg_reward = sum(last_100_episode_rewards) / len(last_100_episode_rewards)
            if i_episode % 1000 == 0:
                print("\rEpisode {}/{} || Best average reward {}\n".format(i_episode, num_episodes, avg_reward), end="")

    print()


def testing_after_learning(Q, mode):
    agent = Agent(Q, mode)
    n_tests = 100
    total_test_rewards = []
    for episode in range(n_tests):
        state = env.reset()
        episode_reward = 0

        while True:
            action = agent.select_action(state)
            new_state, reward, done, _ = env.step(action)
            episode_reward += reward

            if done:
                total_test_rewards.append(episode_reward)
                break

            state = new_state

    print("avg: " + str(sum(total_test_rewards) / n_tests))


Q = defaultdict(lambda: np.zeros(action_size))
while True:
    
    print()
    print("1. testing without learning")
    print("2. MC-control")
    print("3. q-learning")
    print("4. exit")
    menu = int(input("select: "))
    if menu == 1:
        testing_without_learning()
    elif menu == 2:
        np.random.seed(1)
        env.reset(seed=1)
        Q = defaultdict(lambda: np.zeros(action_size))
        model_free_RL(Q, "mc_control")

        np.random.seed(7777)
        env.reset(seed=7777)
        testing_after_learning(Q, "test_mode")
    elif menu == 3:
        np.random.seed(1)
        env.reset(seed=1)
        Q = defaultdict(lambda: np.zeros(action_size))
        model_free_RL(Q, "q_learning")

        np.random.seed(7777)
        env.reset(seed=7777)
        testing_after_learning(Q, "test_mode")
    elif menu == 4:
        break
    else:
        print("wrong input!")
