import main_lib
from frozenlake import FrozenLakeEnv

while True:
    mode = int(input("1.Not Slippery, 2.Slippery: "))
    if mode == 1:
        env = FrozenLakeEnv(is_slippery=False)
        break
    elif mode == 2:
        env = FrozenLakeEnv(is_slippery=True)
        break
    else:
        print("잘못 입력했습니다.")

# 환경 state 개수 및 action 개수
#print(env.nS, env.nA)

while True:
    mode = int(input("1.Policy Iteration, 2.Value Iteration: "))
    if mode == 1:
        policy, V = main_lib.policy_iteration(env)
        break
    elif mode == 2:
        policy, V = main_lib.value_iteration(env)
        break
    else:
        print("잘못 입력했습니다.")
print()

# print( env.MDP[0][1] )
# state 0 에서 action 1 을 선택했을 때 [상태 이동 확률, 도착 state, reward]

print("Optimal State-Value Function:")
for i in range(len(V)):
    if i>0 and i%4==0:
        print()
    print('{0:0.3f}'.format(V[i]), end="\t")
print("\n")

print("Optimal Policy [LEFT, DOWN, RIGHT, UP]:")
action = {0:"LEFT", 1:"DOWN", 2:"RIGHT", 3:"UP"}
for i in range(len(policy)):
    if i>0 and i%4==0:
        print()
    print(policy[i], end='    ')
print()
