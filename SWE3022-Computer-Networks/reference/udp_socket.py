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
        h1 = self.addHost('h1')
        h2 = self.addHost('h2')
        s1 = self.addSwitch('s1')
        self.addLink(h1, s1)
        self.addLink(h2, s1)




def main():
    topo = SimpleTopology()
    net = Mininet( topo=topo)

    net.start()

    h1 = net.get('h1')
    h2 = net.get('h2')

    h2.cmd('python3 udp_server.py &')

    time.sleep(1)

    start_time = time.time()

    result = h1.cmd('python3 udp_client.py 10.0.0.2')
    

    end_time = time.time()


    rtt = (end_time - start_time) * 1000
    print("Round-trip time: {0:.2f} ms".format(rtt))
    print(result)





    net.stop()

if __name__ == '__main__':
    setLogLevel('info')
    main()
