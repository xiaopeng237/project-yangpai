#!/bin/bash

app_arry=( yangpi_service_mysql yangpi_service_i2cbus yangpi_service_adjust yangpi_service_rtu yangpi_service_ota yangpi_service_pioneers)
app_path="/mnt/target/bin/"
app_status=(VmSize VmRSS VmData VmStk VmExe VmLib)


function app_status_c(){

    for app_status_name in ${app_status[*]}
    do
        echo "awk '/$app_status_name/{print \"$(date "+%Y-%m-%d %H:%M:%S")\",\$1,\$2,\$3}' /proc/$1/status >> /mnt/$2_status" |bash
    done

    echo " -------------------------------------" >> /mnt/$2_status

    COUNT=$(wc -c < /mnt/$2_status)
    if [ $COUNT -ge 52428800 ]; then
        rm /mnt/$2_status
    fi

}


sed -ri '/\/mnt\/target/d' /etc/profile

sed -i '$a\LD_LIBRARY_PATH=/mnt/target/lib:/usr/local/mysql/lib/mysql/:/usr/local/mysql/lib'  /etc/profile
sed -i '$a\export PATH=$PATH:/mnt/target/bin' /etc/profile

/mnt/target/bin/dlt-daemon -c /mnt/target/etc/dlt.conf &


source /etc/profile

if [ -f /tmp/dbus_service.pid ]; then
	rm /tmp/dbus_service.pid
fi

/mnt/target/bin/dbus-daemon --fork --print-address --config-file=/mnt/target/pandadbus.conf
if [ $? -ne 0 ]; then
	rm /tmp/dbus_service.pid
	/mnt/target/bin/dbus-daemon --fork --print-address --config-file=/mnt/target/pandadbus.conf
fi

sleep 5

while true
do
    for app_name in ${app_arry[*]}
    do
        {
            COUNT=$(ps |grep $app_name |grep -v "grep" |wc -l )
            echo $COUNT &>/dev/null
            pid=$(ps |grep $app_name |grep -v "grep" |awk -F' ' '{print $1}')
            if [ $COUNT -eq 0 ]; then
                    $app_path$app_name &
                    echo "!!!!!!!$app_name NOT RUN!!!!!!! `date`" >> /mnt/${app_name}_reboot
                    echo $app_name NOT RUN
            else
                    app_status_c $pid $app_name
                    echo $app_name is RUN
            fi
        }
    done

#    wait

    sleep 60
done

