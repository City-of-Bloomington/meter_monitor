include make.conf
# Variables from make.conf:
#
# DOCKER_REPO

SHELL := /bin/bash
APPNAME := meter_monitor

SASS := $(shell command -v sassc 2> /dev/null)
MSGFMT := $(shell command -v msgfmt 2> /dev/null)
LANGUAGES := $(wildcard language/*/LC_MESSAGES)

VERSION := $(shell cat VERSION | tr -d "[:space:]")
COMMIT := $(shell git rev-parse --short HEAD)

default: clean compile package

deps:
ifndef SASS
	$(error "sassc is not installed")
endif
ifndef MSGFMT
	$(error "gettext is not installed")
endif

clean:
	rm -Rf build/${APPNAME}*

compile: deps $(LANGUAGES)
	cd public/css/local && sassc -t compact -m screen.scss screen.css

package:
	[[ -d build ]] || mkdir build
	rsync -rl --exclude-from=buildignore . build/${APPNAME}
	cd build && tar czf ${APPNAME}-${VERSION}.tar.gz ${APPNAME}

dockerfile:
	docker build build/${APPNAME} -t ${DOCKER_REPO}/${APPNAME}:${VERSION}-${COMMIT}
	docker push ${DOCKER_REPO}/${APPNAME}:${VERSION}-${COMMIT}

$(LANGUAGES): deps
	cd $@ && msgfmt -cv *.po
