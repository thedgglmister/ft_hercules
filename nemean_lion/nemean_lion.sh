sed -i 's/^deb cdrom/# deb cdrom/g' /etc/apt/sources.list
apt-get -y update
apt-get -y install openssh-server
sed -i 's/^.*Port.*/Port 50000/g' /etc/ssh/sshd_config
service ssh restart