+==============================================================================+
|                                 datetime-lock                                |
+==============================================================================+
+------------------------------------------------------------------------------+
| datetime-lock: A security tool who denies physical access to your system.    |
|                                                                              |                                                  
| Writing by: Eddie Brüggemann                                                 |
| Writing programming language: C                                              |
| Writing start: 09/07/13                                                      |
| Writing end: 15/08/13                                                        |
| Revision: 26/09/13                                                           |
| Contact: mrcyberfighter@gmail.com                                            |
| Credits: Thank's to my mother and to the doctors,                            |
|          Stay away from drugs, drugs destroy your brain and your life.       |
|                                                                              |
+------------------------------------------------------------------------------+
+==============================================================================+
|                                  Description                                 |
+==============================================================================+
| datetime-lock is a little configurable security tool who can deny the        |
| access to your system according to the configuration of the programm.        |
| How does it work ?                                                           |
| datetime-lock must be first configurated throught the different available    |
| command-line options, giving multiple ways to set:                           |
| -A start date and a start time.                                              |
| -An end date and an end time.                                                |
| Or with the regular date settings to set as:                                 |
| -A or some specific days of week like:                                       |
|   -> --today                                                                 |
|   -> --weekend-days (saturday and sunday).                                   |
|   -> --week-days (monday, thuesday, wednesday, thursday and friday.)         |
|   -> --days (The selected days from the weekdays list.)                      |
| During this time, slice your system is protected against some physical       |
| present offender with bad intentions, like cracking your password, even if   |
| he does not know it before the violation of your home, your workplace or     |
| where ever your system is located.                                           |
|                                                                              |
| After datetime-lock configuration the programm print a summary with the      |
| currently settings.                                                          |
| !!! The programm does not ask for any confirmation: if you make an mistake   |
|     during the configuration, you will see it in the clear printed summary;  |
|     if you want to reset the settings do not block the system with an error  |
|     way you must call the --disable option who will reset the configuration  |
|     so that your system is not locked with datetime-lock.                    |
|                                                                              |
|     Anyway else the locking is now activated and your system is untouchable  |
|     for the configurated time slice.                                         |
|                                                                              |
| The locking mechanism is an automatic directly shutdown process who will     |
| prevent from bad intentions intruder, to tip the password, even if he        |
| knows it, because the system will automatically shutdown by booting.         |
|                                                                              |
| In addition datetime-lock log system attemps which you can read with the     |
| --display-logs options.                                                      |
|                                                                              |
| Note: take care by the special time setting midnight because midnight is     |
|       the first time from the current day.                                   |
|                                                                              |
+------------------------------------------------------------------------------+
+==============================================================================+
|                                datetime-config                               |
+==============================================================================+
| datetime-config is an little utility to help an regular configuration of     |
| datetime-lock in case of an automatic configuration with cron, useable with  |
| the substitution command:                                                    |
| $ $(datetime-config -s) # per example                                        |
| Who support following options:                                               |
|                                                                              |
|       -s              [start]                                                |
|       -d  hh:mm:ss    [date]                                                 |
|       -t  hh:mm:ss    [time]                                                 |
|                                                                              |
| Sea using examples in the file: usage_examples.txt                           |
|                                                                              |
+------------------------------------------------------------------------------+
+==============================================================================+
|                                    Advices                                   |
+==============================================================================+
| If you are a  "security paranoid"  like me I can give you the following      |
| advices who are not often used:                                              |
| -> Setting an password for the BIOS.                                         |
| -> Disable the CD-ROM | USB booting options in the BIOS.                     |
| -> Set an padlock on your computer if it is possible, look if the are empty  |
|    round pin on the computer opening mechanism, in addition or for the open  |
|    box security.                                                             |
| -> If you have an key protected box where to set the computer in, with alls  |
|    for the air set your computer in or by you an adapted furniture.          |
|                                                                              |
+------------------------------------------------------------------------------+
+==============================================================================+
|                                 Installation                                 |
+==============================================================================+
| Decompress the tarball:                                                      |
| $ tar -xf datetime-lock.tar                                                  |
| Change the currrent directory to the extracted folder.                       |
| $ cd /datetime-lock                                                          |
| Run the installation script called install.sh                                |
| $ . install.sh                                                               |
| datetime-lock is now correctly installed and you can remove the extracted    | 
| folder.                                                                      |
|                                                                              |
| If you want to remove datetime-lock from your system.                        |
| Run the desintallation script: desinstallation.sh                            | 
| $ . desinstallation.sh                                                       |
| datetime-lock is now completely removed from you system.                     |
|                                                                              |
+------------------------------------------------------------------------------+
+==============================================================================+
|                                  Copyright                                   |
+==============================================================================+
| This programm is under copyright from the GPL GNU GENERAL PUBLIC LICENSE     |
+------------------------------------------------------------------------------+
+==============================================================================+
| datetime-lock and datetime-config denies physical access to your system.     |
| Copyright (C) 2013 Bruggeman Eddie.                                          |
|                                                                              |
| This file is part of datetime-lock and datetime-config.                      |
| datetime-lock and datetime-config are free software:                         | 
| you can redistribute it and/or modify it under the terms of                  |
| the GNU General Public License as published by                               |
| the Free Software Foundation, either version 3 of the License, or            |  
| (at your option) any later version.                                          | 
|                                                                              | 
| datetime-lock and datetime-config are distributed in the hope that it will   |
| be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of    |
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                 |
| GNU General Public License for more details.                                 | 
|                                                                              |
| You should have received a copy of the GNU General Public License            |
| along with datetime-lock and datetime-config.                                | 
| If not, see <http://www.gnu.org/licenses/>                                   |    
+------------------------------------------------------------------------------+
+==============================================================================+



