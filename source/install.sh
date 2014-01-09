#!/bin/bash

############################################################################
#                                                                          #
# This programm is under copyright from the GPL GNU GENERAL PUBLIC LICENSE #
#                                                                          #
############################################################################

sudo echo "Start installation from datetime-lock"

if [[ $? != 0 ]] ;
then
echo "You must run this installation script as root."
return 1
fi

cd "$PWD/Files/"

gcc -Wall -Wextra datetime-lock.c -o datetime-lock 2> /dev/null # Don't display the 4 four strftime warnings from the justification use by this function.

sudo mv datetime-lock /usr/local/bin/ # move the binary to users binary folder



sudo chown root:root /usr/local/bin/datetime-lock  # datetime-lock must be run as root only. 
sudo chmod go-rwx /usr/local/bin/datetime-lock     # datetime-lock must be run as root only.  

cd ..
gcc -Wall -Wextra datetime-config.c -o datetime-config # Compilation of the datetime-lock configuration utility.
sudo mv datetime-config /usr/local/bin/ # move the binary to users binary folder.


sudo cp datetime-lock.sh /etc/init.d/ # Move the start-up script to the start-up scripts folder.

run_level=$(runlevel)

sudo ln -s /etc/init.d/datetime-lock.sh /etc/rc${run_level/"N "/}.d/S50Datetime-lock # Link the start-up script to the runlevel 2 foler: /etc/rc2.d/ 
											# To adapt if the result from the command runlevel is different from 2. 

sudo chown root:root /etc/init.d/datetime-lock.sh # Set the owner the root user.                
sudo chmod a+rwx /etc/init.d/datetime-lock.sh     # Make the start-up script executable. 

sudo echo "datetime-lock correctly installed on your system."

