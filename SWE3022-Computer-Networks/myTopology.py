from mininet.net import Mininet
from mininet.topo import Topo
from mininet.node import OVSKernelSwitch    
from mininet.cli import CLI
from mininet.node import Host
from mininet.log import setLogLevel, info
from mininet.link import Link, TCLink

bandwidth = 500 # Mbps
delay = '1ms'
loss = 0.1 # percent
jitter = '0ms' #

class TreeTopology(Topo):
    def __init__(self, depth=2, degree=4):
        self.depth = depth
        self.degree = degree
        super().__init__()

    def build(self):
        nodes = [[]]
        
        # Add level 0(root) switch
        self.addSwitch('l0-1', cls=OVSKernelSwitch, failMode='standalone')
        nodes[0] = ['l0-1']
        
        # Add level 1 ~ (depth - 1) switches
        for l in range(1, self.depth):
            nodes.append([])
            for n in range(self.degree ** l):
                name = 'l{}-{}'.format(l, n + 1)
                self.addSwitch(name, cls=OVSKernelSwitch, failMode='standalone')
                nodes[l].append(name)
        
        # Add Hosts (level depth)
        nodes.append([])
        for h in range(self.degree ** self.depth):
            name = 'h{}'.format(h + 1)
            self.addHost(name, cls=Host, defaultRoute=None)
            nodes[self.depth].append(name)

        # Link all nodes as tree structure
        l = self.depth
        for l_nodes in reversed(nodes[1:]):
            for idx, cur_node in enumerate(l_nodes):
                par_node = 'l{}-{}'.format(l-1, idx // self.degree + 1)
                self.addLink(cur_node, par_node, cls=TCLink,
                            bw=bandwidth, delay=delay, loss=loss,
                            jitter=jitter)
            l -= 1

# bandwidth = 1000 # Mbps
# delay = '0ms'
# loss = 0 # percent

class DegreeTopology(Topo):
    def __init__(self, degrees : tuple):
        self.depth = len(degrees)
        self.degrees = degrees # (1, 2, ...) number of nodes of each level in topology
        self.n_nodes = []
        tmp = 1
        for i in self.degrees:
            tmp *= i
            self.n_nodes.append(tmp)
        super().__init__()
    
    def build(self):
        nodes = []

        # Add switches
        for i, n_node in enumerate(self.n_nodes[:-1]):
            nodes.append([])
            for j in range(n_node):
                name = 'l{}-{}'.format(i+1, j+1)
                self.addSwitch(name, cls=OVSKernelSwitch, failMode='standalone')
                nodes[i].append(name)
        
        # Add hosts
        nodes.append([])
        for i in range(self.n_nodes[-1]):
            name = 'h{}'.format(i+1)
            self.addHost(name, cls=Host, defaultRoute=None)
            nodes[-1].append(name)
        
        # Add links
        l = self.depth - 1
        for levels in reversed(nodes[1:]):
            n = self.n_nodes[l] // self.n_nodes[l-1]
            for i, node in enumerate(levels):
                upper_node = 'l{}-{}'.format(l, i // n + 1)
                self.addLink(node, upper_node, cls=TCLink,
                             bw=bandwidth, delay=delay, loss=loss)
            l -= 1
        
        for i in range(len(nodes[0])-1):
            self.addLink(nodes[0][i], nodes[0][i+1], cls=TCLink,
                         bw=bandwidth, delay=delay, loss=loss)
