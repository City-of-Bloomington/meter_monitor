#!/bin/bash
# Creates a tarball containing a full snapshot of the data in the site
#
# @copyright Copyright 2011-2017 City of Bloomington, Indiana
# @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
APPLICATION_NAME="meters"
MYSQLDUMP="/usr/bin/mysqldump"
MYSQL_DBNAME="${APPLICATION_NAME}"
MYSQL_CREDENTIALS="/etc/cron.daily/backup.d/${APPLICATION_NAME}.cnf"
BACKUP_DIR="/srv/backups/${APPLICATION_NAME}"
APPLICATION_HOME="/srv/sites/${APPLICATION_NAME}"
SITE_HOME="${APPLICATION_HOME}/data"

# How many days worth of tarballs to keep around
num_days_to_keep=5

#----------------------------------------------------------
# No Editing Required below this line
#----------------------------------------------------------
now=`date +%s`
today=`date +%F`

# Dump the database
$MYSQLDUMP --defaults-extra-file=$MYSQL_CREDENTIALS $MYSQL_DBNAME > $SITE_HOME/$MYSQL_DBNAME.sql
cd $SITE_HOME
tar czf $today.tar.gz $MYSQL_DBNAME.sql
mv $today.tar.gz $BACKUP_DIR

# Purge any backup tarballs that are too old
cd $BACKUP_DIR
for file in `ls`
do
    atime=`stat -c %Y $file`
    if [ $(( $now - $atime >= $num_days_to_keep*24*60*60 )) = 1 ]
    then
        rm $file
    fi
done
