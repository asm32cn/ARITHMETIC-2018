@echo off

set strCmd=go build -ldflags="-w -s" SchulteGrid-2018-go-demo1.go

echo #%strCmd%
%strCmd%

pause
