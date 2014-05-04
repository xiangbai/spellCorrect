#!/bin/bash
#script=$1

script="server"

case $1 in
	start)
		if[ $(ps -ef | grep $script | grep -v `grep` | wc -l) -gt 0 ]
		then
			echo "$script already started"
		else
			echo "$script starting....."
			./$script 
			echo "$script started"
		fi
		;;
	restart)
		echo "$script restarting....."
		if[ $(ps -ef | grep $script | grep -v `grep` | wc -l) -gt 0 ]
		then
			echo "$script stopping....."
			killall -9 $script
			killall -9 sleep
			echo "$script stoped"
		fi
		if[ $(ps -ef | grep $script | grep -v `grep` | wc -l) -eq 0 ]
		then
			echo "$script starting...."
			./$script &
			echo "$script started"
		else
			echo "$script restart failure"
		fi
		;;
	stop)
		if[ $(ps -ef | grep $script | grep -v `grep` | wc -l) -gt 0 ]
		then
			echo "$script stopping...."
			killall -9 $script
			killall -9 sleep 
			echo "script stoped"
		else
			echo "$script alread stopped"
		fi
		;;
	--help)
		echo "Usage: shell.sh [OPTION]"
		echo "To control $script"
		echo "Example: shell.sh start[restart|stop|status]"
		;;
	*)
		echo "Usage: shell.sh [OPTION]"
		echo "Try 'shell.sh --help' for more information."
		;;
esac

exit 0 
