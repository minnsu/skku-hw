import gym
import numpy as np
import matplotlib.pyplot as plt
import torch
from agent import Agent
import time

LOG_INTERVAL = 1000
TRAIN_STEPS = 50000

env = gym.make('CartPole-v1')

action_size = env.action_space.n
print("Action Space", env.action_space.n)
print("State Space", env.observation_space.shape[0])


def visualize_env(agent=None):
    state = env.reset()
    total_rewards = 0

    for step in range(200):
        env.render(mode='human')
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


def plot_with_exponential_averaging(x, y, label, alpha):
    y_ema = [y[0],] 
    for y_i in y[1:]:
        y_ema.append(y_ema[-1] * alpha + y_i * (1 - alpha))
    
    p = plt.plot(x, y_ema, label=label)
    
    plt.plot(x, y, color=p[0].get_color(), alpha=0.2)
    
    plt.show()


def model_free_RL():
    agent = Agent(env.observation_space.shape[0], env.action_space.n)
    curr_step = 0
    episode_rewards = 0
    all_episode_rewards = []
    all_20_epi_rewards = []
    episode_end_steps = []
    
    state = env.reset()
    while curr_step < TRAIN_STEPS:
        action = agent.select_action(state)
        next_state, reward, done, _ = env.step(action)
        agent.step(state, action, reward, next_state, done)

        episode_rewards += reward
        state = next_state

        if done:
            state = env.reset()
            all_episode_rewards.append(episode_rewards)
            episode_end_steps.append(curr_step)
            episode_rewards = 0

        curr_step += 1

        if curr_step % 1000 == 0:
            last_20_avg_reward = np.mean(all_episode_rewards[-20:])
            all_20_epi_rewards.append(last_20_avg_reward)
            print(f"\rStep {curr_step}/{TRAIN_STEPS} || Cur average reward {last_20_avg_reward} "
                    f"|| Max average reward {max(all_20_epi_rewards)} || Max reward {max(all_episode_rewards)}", end="")
            if np.mean(all_episode_rewards[-20:]) > 475:
                print('\nEarly Stop')
                break
    
    plot_with_exponential_averaging(episode_end_steps, all_episode_rewards, label='DQN', alpha=0.9)

    print('\n')
    return agent


def testing_after_learning(agent):
    n_tests = 100
    total_test_rewards = []
    xs = []
    for episode in range(n_tests):
        state = env.reset()
        episode_reward = 0

        while True:
            action = agent.select_action(state, is_test=True)

            next_state, reward, done, _ = env.step(action)
            episode_reward += reward
            xs.append(state[0])

            if done:
                total_test_rewards.append(episode_reward)
                break

            state = next_state

    print("Test Reward Result: " + str(sum(total_test_rewards) / n_tests))
    print("Test Average x Result: " + str(np.average(xs)))



while True:
    print("1. Visualize without Learning")
    print("2. DQN Learning")
    print("3. Visualize after Learning")
    print("4. Exit")
    menu = int(input("select: "))
    if menu == 1:
        visualize_env()
    elif menu == 2:
        np.random.seed(1)
        env.reset(seed=1)
        torch.manual_seed(1)
        agent = model_free_RL()

        np.random.seed(7777)
        env.reset(seed=7777)
        torch.manual_seed(7777)
        testing_after_learning(agent)
    elif menu == 3:
        visualize_env(agent)
    elif menu == 4:
        break
    else:
        print("wrong input!")
