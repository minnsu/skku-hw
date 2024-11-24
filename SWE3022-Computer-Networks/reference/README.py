# Execution
# mininet:
#   sudo mn
# python file:
#   sudo python3 ___.py

from mininet.net import Mininet
from mininet.topo import Topo
from mininet.node import OVSKernelSwitch    
from mininet.cli import CLI
from mininet.node import Host
from mininet.log import setLogLevel, info
from mininet.link import Link, TCLink, TCIntf

# Network topology definition
class Topology(Topo):
    def build(self):
        # add Host to topology
        h1 = self.addHost('host name', cls=Host, defaultRoute=None)
        
        # add Switch to topology
        s1 = self.addSwitch('switch name', cls=OVSKernelSwitch, failMode='standalone')
        
        # add Link of host obj and switch obj
        # with bandwidth, delay, loss: kind of network property
        self.addLink(h1, s1, cls=TCLink, bw=10000000, delay='0.1ms', loss=0.1)

# Network testing
def main():
    topo = Topology()
    net = Mininet(topo=topo, autoSetMacs=True, build=False, ipBase='10.0.0.0/24')

    # network start
    net.start()

    # get host object
    src, dst = net.getNodeByName('host name1'), net.getNodeByName('host name2')
    src, dst = net.hosts[0], net.hosts[1]
    
    # set host ip with interface and ip
    src.setIP(intf='h1-eth0', ip='10.0.0.1/24')
    dst.setIP(intf='h2-eth0', ip='10.0.0.2/24')

    # iperf: throughput measuring program
    net.iperf([src, dst], seconds=10) # measure through of seconds
    
    # open mininet terminal
    CLI(net)

    # network stop
    net.stop()