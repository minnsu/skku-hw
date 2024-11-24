from mininet.net import Mininet
from mininet.topo import Topo
from mininet.node import OVSKernelSwitch    
from mininet.cli import CLI
from mininet.node import Host
from mininet.log import setLogLevel, info
from mininet.link import Link, TCLink
import socket
import time


class SimpleTopology(Topo):
    def build(self):
        h1 = self.addHost('h1', cls=Host, defaultRoute=None)
        h2 = self.addHost('h2', cls=Host, defaultRoute=None)
        s1 = self.addSwitch( 's1', cls=OVSKernelSwitch, failMode='standalone')
        self.addLink(h1, s1, cls=TCLink, bw=10000000, delay='0.1ms', loss=0.1)
        
        self.addLink(h2, s1, cls=TCLink, bw=10000000, delay='0.1ms')
        #self.addLink(h2, s1)



def main():
    topo = SimpleTopology()
    net = Mininet( topo=topo, autoSetMacs=True, build=False, ipBase="10.0.0.0/24")

#    net.build()
    net.start()

    h1 = net.getNodeByName('h1')
    h2 = net.getNodeByName('h2')

    h1.setIP(intf="h1-eth0", ip="10.0.0.1/24")
    h2.setIP(intf="h2-eth0", ip="10.0.0.2/24")
    src, dst = net.hosts[0], net.hosts[1]
    s_bw, c_bw = net.iperf([src, dst], seconds=10)
    info(s_bw)
    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel('info')
    main()
