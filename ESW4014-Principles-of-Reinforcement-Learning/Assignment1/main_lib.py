import numpy as np

'''
def policy_evaluation(env, policy, gamma=0.99, theta=1e-8):
    V = np.zeros(env.nS)

    return V

def policy_improvement(env, V, gamma=0.99):
    policy = np.zeros([env.nS, env.nA]) / env.nA

    return policy
'''


def policy_iteration(env, gamma=0.99, theta=1e-8):
    V = np.zeros(env.nS)
    policy = np.ones([env.nS, env.nA]) / env.nA

    is_optimal = False
    while not is_optimal:

        # Policy evaluation
        is_converge = False
        while not is_converge:
            delta = 0
            for s in range(env.nS):
                prev_vs = V[s].copy()

                expectation = 0
                for a in range(env.nA):
                    action_prob = policy[s, a]
                    mdps = env.MDP[s][a]

                    for mdp in mdps:
                        transition_prob, next_state, reward = mdp
                        expectation += action_prob * transition_prob * (reward + gamma * V[next_state])

                V[s] = expectation
                delta = max(delta, np.abs(prev_vs - V[s]))

            if delta < theta:
                is_converge = True

        # Policy improvement
        policy_stable = True
        old_policy = policy.copy()
        for s in range(env.nS):

            q_values = []
            for a in range(env.nA):
                mdps = env.MDP[s][a]

                expectation = 0
                for mdp in mdps:
                    transition_prob, next_state, reward = mdp
                    expectation += transition_prob * (reward + gamma * V[next_state])
                
                q_values.append(expectation)

            policy[s] = np.zeros((4))
            policy[s, np.argmax(q_values)] = 1
            if any(policy[s] != old_policy[s]):
                policy_stable = False
        
        if policy_stable:
            is_optimal = True

    return policy, V

def value_iteration(env, gamma=0.99, theta=1e-8):
    V = np.zeros(env.nS)
    policy = np.ones([env.nS, env.nA]) / env.nA

    is_converge = False
    while not is_converge:
        delta = 0

        for s in range(env.nS):
            prev_vs = V[s].copy()
            
            q_values = []
            for a in range(env.nA):
                mdps = env.MDP[s][a]

                expectation = 0
                for mdp in mdps:
                    transition_prob, next_state, reward = mdp
                    expectation += transition_prob * (reward + gamma * V[next_state])
                
                q_values.append(expectation)
            
            V[s] = max(q_values)
            policy[s] = np.zeros(4)
            policy[s, np.argmax(q_values)] = 1

            delta = max(delta, np.abs(prev_vs - V[s]))

        if delta < theta:
            is_converge = True

    return policy, V