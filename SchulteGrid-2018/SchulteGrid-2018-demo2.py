#!/usr/bin/env python
# -*- encoding: utf-8 -*-

# Python 2.7
# SchulteGrid-2018-demo2.py

import random, web

urls = (
	'/', 'index'
)

bindDigitId = {
	1: 'firstDigit',
	25: 'lastDigit'
}

def getList():
	nCount = 25
	_source = [{'n': n, 'next': n} for n in xrange(1, nCount + 1)]
	_list = [0] * nCount
	_list_ptr = 0

	current = 0
	prev = nCount - 1
	_source[prev]['next'] = current
	for i in xrange(nCount):
		r = random.randint(0, nCount - i - 1)
		for n in xrange(r):
			prev = current
			current = _source[current]['next']
		_list[_list_ptr] = _source[current]['n']
		_list_ptr += 1

		_source[prev]['next'] = _source[current]['next']
		_source[current]['next'] = -1
		current = _source[prev]['next']

	return _list


class index():
	def GET(self):
		return '<!doctype html>\n' \
			'<html>\n' \
			'<head><title>SchulteGrid-2018-demo1</title>\n' \
			'<style>\n' \
			'body { background-color: #a5cbf7; }\n' \
			'span { position:absolute; top:20px; right:20px; font-size:56px;}\n' \
			'ul { display:block; margin:0px; padding:0px; width:500px; height:500px; border-right:1px solid #666; border-bottom:1px solid #666; }\n' \
			'li { display:block; margin:0px; padding:0px; float:left; width: 99px; height:99px; line-height: 99px; text-align:center; border-left:1px solid #666; border-top:1px solid #666; font-size:64px; }\n' \
			'</style>\n' \
			'</head>\n' \
			'<body>\n\n' \
			'<h1>SchulteGrid-2018-demo1</h1>\n\n' \
			'<ul>\n' + \
			'\n'.join( [ '\t<li%s>%s</li>' % (' id="' + bindDigitId[i] + '"' if bindDigitId.has_key(i) else '', i) for i in getList() ] ) + \
			'</ul>\n\n' \
			'<span></span>\n' \
			'<script>\n' \
			'var txtDisplay = document.getElementsByTagName("span")[0];\n' \
			'var dateStart = null;\n' \
			'var intervalId = null;\n' \
			'function PA_js_initStartDate(){\n' \
			'\tdateStart = new Date();\n' \
			'}\n' \
			'function PA_js_doDisplay(){\n' \
			'\ttxtDisplay.innerHTML = (((new Date()) - dateStart) / 1000 ).toFixed(3);\n' \
			'}\n' \
			'function PA_js_clearTimer(){\n' \
			'\tclearInterval(intervalId);\n' \
			'\tintervalId = null;\n' \
			'}\n' \
			'function PA_js_startTimer(){\n' \
			'\tif( intervalId ) PA_js_clearTimer();\n' \
			'\tPA_js_initStartDate();\n' \
			'\tintervalId = setInterval( PA_js_doDisplay, 100 );\n' \
			'}\n' \
			'txtDisplay.onclick = PA_js_initStartDate;\n' \
			'PA_js_startTimer()\n' \
			'document.getElementById("firstDigit").onclick = PA_js_startTimer;\n' \
			'document.getElementById("lastDigit").onclick = PA_js_clearTimer;\n' \
			'</script>\n\n' \
			'</body>\n' \
			'</html>'

if __name__ == '__main__':
	web.application(urls, globals()).run()
