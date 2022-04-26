#!/bin/sh

ps | grep -q "dbus-daemon"  | grep -vq "grep"

if [ $? -eq 0 ] ;then
	/mnt/target/bin/yangpi_service_pioneers &
	/mnt/target/bin/yangpi_service_mysql &
	/mnt/target/bin/yangpi_service_i2cbus &
	/mnt/target/bin/yangpi_service_adjust &
	exit
fi



sed -ri '/\/mnt\/target/d' /etc/profile

echo "export LD_LIBRARY_PATH=/mnt/target/lib" >>/etc/profile
echo "export PATH=$PATH:/mnt/target/bin" >>/etc/profile

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

/mnt/target/bin/yangpi_service_pioneers &
/mnt/target/bin/yangpi_service_mysql &
/mnt/target/bin/yangpi_service_i2cbus &
/mnt/target/bin/yangpi_service_adjust &
/mnt/target/bin/yangpi_service_rtu &
/mnt/target/bin/yangpi_service_ota &