#!/bin/bash

############################################################################
#                                                                          #
# This programm is under copyright from the GPL GNU GENERAL PUBLIC LICENSE #
#                                                                          #
############################################################################

sudo echo "Start desinstallation from datetime-lock"

if [[ $? != 0 ]] ;
then
echo "You must run this desinstallation script as root."
return 1
fi

sudo rm /usr/local/bin/datetime-lock
sudo rm /usr/local/bin/datetime-config
sudo rm /etc/init.d/datetime-lock.sh

run_level=$(runlevel)

sudo unlink /etc/rc${run_level/"N "/}.d/S50Datetime-lock 

sudo rm -R /usr/share/datetime-lock 2> /dev/null

sudo echo "datetime-lock successfully removed from your system"