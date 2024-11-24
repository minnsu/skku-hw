from mininet.net import Mininet
from mininet.cli import CLI
from mininet.log import setLogLevel, info
import time

from myTopology import DegreeTopology


def main():
    topo = DegreeTopology((2, 4, 4))
    n_hosts = topo.n_nodes[-1]

    net = Mininet(topo=topo, autoSetMacs=True, build=False, ipBase='10.0.0.1/24')

    net.start()

    base = '10.0.0.{}'
    for i, host in enumerate(net.hosts):
        host.cmd('python3 tcp_server.py {} &'.format(base.format(i + 1)))
    
    time.sleep(1)
    for i, host in enumerate(net.hosts):
        ser = base.format(n_hosts - i)        
        result = host.cmd('python3 tcp_client.py {} &'.format(ser))
    
    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel('info')
    main()