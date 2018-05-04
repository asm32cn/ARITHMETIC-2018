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

	current = 0
	prev = nCount - 1
	_source[prev]['next'] = current
	for i in xrange(nCount):
		r = random.randint(0, nCount - i - 1)
		for n in xrange(r):
			prev = current
			current = _source[current]['next']

		_list[i] = _source[current]['n']

		_source[prev]['next'] = _source[current]['next']
		_source[current]['next'] = -1
		current = _source[prev]['next']

	return _list


class index():
	def GET(self):
		return '<!doctype html>\n' \
			'<html>\n' \
			'<head><title>SchulteGrid-2018-demo2</title>\n' \
			'<style>\n' \
			'body { background-color: #a5cbf7; }\n' \
			'h1 { font-size: 72px; margin:0px; padding:0px; line-height: 150%;}\n' \
			'ul { display:block; margin:0px; padding:0px; float:left; width:500px; height:500px; border-right:1px solid #666; border-bottom:1px solid #666; }\n' \
			'li { display:block; margin:0px; padding:0px; float:left; width: 99px; height:99px; line-height: 99px; text-align:center; border-left:1px solid #666; border-top:1px solid #666; font-size:64px; }\n' \
			'</style>\n' \
			'</head>\n' \
			'<body>\n\n' \
			'<h1>SchulteGrid-2018-demo2</h1>\n\n' \
			'<ul>\n' + \
			'\n'.join( [ '\t<li%s>%s</li>' % (' id="' + bindDigitId[i] + '"' if bindDigitId.has_key(i) else '', i) for i in getList() ] ) + \
			'</ul>\n\n' \
			'<script>\n' \
			'function EclapseTime(){\n' \
			'\tvar _this = this;\n' \
			'\tvar intervalId = null;\n' \
			'\tvar startDate = null;\n' \
			'\tvar _button = document.createElement(\'div\');\n' \
			'\tvar displayElapseTime = document.createElement(\'span\');\n' \
			'\t_button.innerHTML = \'Start/Stop\';\n' \
			'\t_button.style.cssText = \'display:block; float:left; font-size:32px; margin:10px 20px; padding: 20px; border:1px solid #069; border-radius:10px; \';\n' \
			'\tdisplayElapseTime.style.cssText = \'position:absolute; right:20px; top:20px; font-size:64px;\';\n' \
			'\tdocument.body.appendChild(_button);\n' \
			'\tdocument.body.appendChild(displayElapseTime);\n' \
			'\n' \
			'\tthis.initStartDate = function(){\n' \
			'\t\tstartDate = new Date();\n' \
			'\t}\n' \
			'\tthis.clearTimer = function(){\n' \
			'\t\tif(intervalId){\n' \
			'\t\t\tclearInterval(intervalId);\n' \
			'\t\t\tintervalId = null;\n' \
			'\t\t}\n' \
			'\t}\n' \
			'\tthis.startTimer = function(){\n' \
			'\t\t_this.clearTimer();\n' \
			'\t\t_this.initStartDate();\n' \
			'\t\tintervalId = setInterval( _this.displayElapsedTime , 100);\n' \
			'\t}\n' \
			'\tthis.displayElapsedTime = function(){\n' \
			'\t\tdisplayElapseTime.innerHTML = ( (new Date() - startDate) / 1000 ).toFixed(3);\n' \
			'\t}\n' \
			'\t_button.onclick = function(){\n' \
			'\t\tif(intervalId){\n' \
			'\t\t\t_this.clearTimer();\n' \
			'\t\t}else{\n' \
			'\t\t\t_this.startTimer();\n' \
			'\t\t}\n' \
			'\t}\n' \
			'}\n' \
			'EclapseTime();\n' \
			'</script>\n\n' \
			'</body>\n' \
			'</html>'

if __name__ == '__main__':
	web.application(urls, globals()).run()

