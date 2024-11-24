import numpy as np

class Agent:

    def __init__(self, Q, mode="test_mode"):
        self.Q = Q
        self.mode = mode
        self.n_actions = 6
        self.eps = 1.0
        self.gamma = 0.85
        self.alpha = 0.1
        
        # original hyper-parameters
        # self.eps = 1.0
        # self.gamma = 0.85
        # self.alpha = 0.1

        self.trajectory = []

    def select_action(self, state):
        """
        Params
        ======
        - state: the current state of the environment

        Returns
        =======
        - action: an integer, compatible with the task's action space
        """

        action = None
        if self.mode == "test_mode":
            action = np.argmax(self.Q[state])
        else:
            if np.random.rand() < self.eps:
                action = np.random.randint(0, self.n_actions)
            else:
                action = np.argmax(self.Q[state])
        
        return action

    def step(self, state, action, reward, next_state, done):
        
        """
        Params
        ======
        - state: the previous state of the environment
        - action: the agent's previous choice of action
        - reward: last reward received
        - next_state: the current state of the environment
        - done: whether the episode is complete (True or False)
        """

        if done:
            if self.eps > 0.01:
                self.eps -= 0.00002

            if self.mode == "mc_control":
                accumulated_reward = 0
                # every-visit MC
                for (state, action, reward) in reversed(self.trajectory):
                    accumulated_reward = reward + self.gamma * accumulated_reward
                    self.Q[state][action] += self.alpha * (accumulated_reward - self.Q[state][action])
                self.trajectory.clear()
        
        if self.mode == "mc_control":
            self.trajectory.append((state, action, reward))
        elif self.mode == "q_learning":
            self.Q[state][action] += self.alpha * (reward + self.gamma * np.max(self.Q[next_state]) - self.Q[state][action])


#  Statistics (training seed=1, testing seed=7777)


# (eps, gamma, alpha) | mc_control | q_learning
# ----------------------------------------------
# (1.0, 0.85, 0.1)    |    7.77    |    8.49    <- best
# (1.0, 0.8,  0.1)    |   -19.51   |    8.49
# (1.0, 0.9 , 0.1)    |    6.66    |    8.49
# (1.0, 0.88, 0.1)    |   -9.59    |    8.49
# (1.0, 0.83, 0.1)    |   -14.06   |    8.49
# (1.0, 0.86, 0.1)    |    6.64    |    8.49
# (1.0, 0.84, 0.1)    |    6.39    |    8.49
# -- manipulating gamma

# (1.0, 0.85, 0.1)    |    7.77    |    8.49    <- best
# (1.0, 0.85, 0.05)   |    7.11    |    8.49
# (1.0, 0.85, 0.07)   |    7.16    |    8.49
# (1.0, 0.85, 0.09)   |    6.41    |    8.49
# (1.0, 0.85, 0.11)   |    4.5     |    8.49
# (1.0, 0.85, 0.13)   |   -47.28   |    8.49
# (1.0, 0.85, 0.2)    |   -91.99   |    8.49
# -- manipulating alpha

# (1.0, 0.85, 0.1)    |    7.77    |    8.49    <- best
# (0.8, 0.85, 0.1)    |    6.84    |    8.49
# (0.6, 0.85, 0.1)    |    7.54    |    8.49
# (0.4, 0.85, 0.1)    |   -22.18   |    8.49
# (0.2, 0.85, 0.1)    |   -99.58   |    8.49
# -- manipulating initial epsilon



# manipulating epsilon decay
#                           | mc_control | q_learning
# -----------------------------------------------------
# limiting minimum to 0.05  |   -54.56   |    8.49
# limiting minimum to 0.03  |   -58.77   |    8.49
# limiting minimum to 0.01  |    7.77    |    8.49    <- best

# decay by 0.00001          |   -1.37    |    8.49
# decay by 0.00002          |    7.77    |    8.49    <- best
# decay by 0.00004          |    2.98    |    8.49
# decay by 0.0001           |    6.54    |    8.49
# decay by 0.001            |   -8.14    |    8.49



# Testing robustness of the best hyper-parameters
# (training seed, testing seed) | mc_control | q_learning
# --------------------------------------------------------
# (1, 7777)                     |    7.77    |    8.49
# (2, 7777)                     |    7.05    |    8.49
# (4, 7777)                     |    6.92    |    8.49
# (8, 7777)                     |   -5.83    |    8.49
# (16, 7777)                    |   -7.83    |    8.49
# (32, 7777)                    |    6.19    |    8.49
# (64, 7777)                    |    6.95    |    8.49

# (1, 1111)                     |    7.2     |    7.47
# (1, 2222)                     |   6.68     |    7.62
# (1, 3333)                     |   7.24     |    7.79
# (1, 4444)                     |   7.23     |    7.81
# (1, 5555)                     |   7.32     |    7.89
# (1, 6666)                     |   7.1      |    8.0
# (1, 8888)                     |   6.82     |    7.22

# ... Maybe robust?