# S6_CSE_NETWORKING_LAB

This repository contains the curriculum and resources for a lab cycle focused on network programming and simulation in Linux. The course aims to equip students with the skills to:

* Utilize network-related commands and configuration files.
* Develop network application programs and protocols.
* Analyze network traffic using monitoring tools.
* Design and configure networks with various protocols.
* Simulate fundamental network concepts using a network simulator.

## Course Outcomes (COs)

* CO1: Proficiency in network commands and configuration files on Linux.
* CO2: Ability to develop network applications and protocols.
* CO3: Expertise in network traffic analysis using monitoring tools.
* CO4: Skills in network design, configuration, and protocol implementation.
* CO5: Understanding of network concepts through simulation.

## Experiments

The lab cycle consists of a series of hands-on experiments covering various aspects of network programming and simulation.

### Day 1: Network Configuration and Commands

**a) Familiarization with Network Configuration Files and Commands**

This section introduces essential network configuration files and commands in Linux. You'll learn about:

* `/etc/init.d/network` (may be deprecated)
* `/etc/sysconfig/network`
* `/etc/sysconfig/network-scripts`
* `/etc/sysconfig/network-scripts/ifcfg-eth0` (example)
* `/etc/nsswitch.conf`
* `/etc/hosts`

**b) Scenario-Based Command Identification**

Imagine you're a system administrator at A123 Company. Use the following commands for specific tasks:

**i) Additional Configuration for the First NIC (Multiple Network Interfaces)**

  - Command: `/etc/sysconfig/network-scripts/ifcfg-eth0` (replace `eth0` with the actual interface name if different)

**ii) Controlling User/IP/Group Searches**

  - Command: `/etc/nsswitch.conf`

**iii) Specifying Routing and Host Information**

  - Commands: A combination of `/etc/sysconfig/network` and interface-specific configuration files (e.g., `/etc/sysconfig/network-scripts/ifcfg-eth0`).

**c) Familiarization with Linux Networking Commands**

This section covers commonly used Linux networking commands:

* `ping`: Tests network connectivity to a host.
* `ifconfig`: Displays network interface configuration details.
* `traceroute`: Traces the route packets take to reach a destination.
* `netstat`: Shows network connections, routing tables, and other network-related information.
* `nslookup`: Looks up DNS records for a hostname or IP address.
* `route`: Manages the routing table.
* `host`: Retrieves information about a hostname or IP address.
* `iwconfig` (wireless interfaces): Configures and displays wireless network interface details.
* `hostname`: Displays or sets the system's hostname.
* `nload` (may require installation): Monitors network traffic.

### Day 2: System Calls for Network Programming

This day focuses on system calls used for network programming in Linux. You'll write C programs to implement:

* **Process Management:** `fork`, `exec`, `getpid`, `exit`, and `wait` system calls.
* **Directory Management:** `opendir`, `readdir`, and `closedir` system calls.
* **File Management:** Copying a file using I/O system calls.

### Days 3-4: Client-Server Communication

You'll implement client-server communication using socket programming in C:

* Day 3: TCP as the transport layer protocol.
* Day 4: UDP as the transport layer protocol.

### Days 5-8: Network Protocol Implementations

These days involve implementing network protocols in C:

* Day 5: Sliding window flow control protocols (Stop and Wait ARQ, Go Back N)
* Day 6: Distance Vector Routing protocol
* Day 7: Simple Mail Transfer Protocol (SMTP)
* Day 8: File Transfer Protocol (FTP)

### Day 9 (Optional): Congestion Control with Leaky Bucket Algorithm

This optional day explores implementing congestion control using the leaky bucket algorithm in C.

### Day 10: Wireshark Tool

You'll gain familiarity with the Wireshark network traffic analysis tool.

### Day 11 (Optional): Network Design and Configuration

This optional day covers designing and configuring a network with multiple subnets, wired and wireless LANs, and common services.

### Day 12: NS2 Simulator

This day introduces the NS2
