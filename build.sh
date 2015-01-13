#!/bin/bash
RELEASE_NAME=meter_monitor
DIR=`pwd`
BUILD=$DIR/build
DIST=$DIR/dist

if [ ! -d $BUILD ]
    then mkdir $BUILD
fi

if [ ! -d $DIST ]
    then mkdir $DIST
fi

# Compile the SCSS
cd $DIR/public/css/local
./build_css.sh
cd $DIR

# The PHP code does not need to actually build anything.
# Just copy all the files into the build
rsync -rlv --exclude-from=$DIR/buildignore --delete $DIR/ $BUILD/

# Create a distribution tarball of the build
tar czvf $DIST/$RELEASE_NAME.tar.gz --transform=s/build/$RELEASE_NAME/ $BUILD
