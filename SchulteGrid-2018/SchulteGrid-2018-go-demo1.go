//SchulteGrid-2018-go-demo1.go
package main

import (
	"container/ring"
	"math/rand"
	"io"
	"log"
	"strconv"
	"net/http"
)

const (
	nCount = 25
	strTitle = "SchulteGrid-2018-go-demo1"
	strHtmlDataA = "<!doctype html>\n" +
		"<html>\n" +
		"<head>\n" +
		"<title>SchulteGrid-2018-go-demo1</title>\n" +
		"<meta name=\"generator\" content=\"editplus\" />\n" +
		"<style>\n" +
		"body { background-color: #a5cbf7; }\n" +
		"h1 { font-size: 72px; margin:0px; padding:0px; line-height: 150%;}\n" +
		"span { position:absolute; top:20px; right:20px; font-size:56px;}\n" +
		"ul { display:block; float:left; margin:0px; padding:0px; width:500px; height:500px; border-right:1px solid #666; border-bottom:1px solid #666; }\n" +
		"li { display:block; margin:0px; padding:0px; float:left; width: 99px; height:99px; line-height: 99px; text-align:center; border-left:1px solid #666; border-top:1px solid #666; font-size:64px; }\n" +
		"#divDisplay { width: 550px; height: 110px; float:left; }\n" +
		"</style>\n" +
		"</head>\n\n" +
		"<body>\n\n" +
		"<h1>SchulteGrid-2018-go-demo1</h1>\n\n\n"
	strHtmlDataB = "\n<script>\n" +
		"function ElapsedTime(){\n" +
		"	var _this = this;\n" +
		"	var intervalId = null;\n" +
		"	var startDate = null;\n" +
		"	var _button = document.createElement('div');\n" +
		"	var displayElapseTime = document.createElement('span');\n" +
		"	_button.innerHTML = 'Start/Stop';\n" +
		"	_button.style.cssText = 'display:block; float:left; font-size:32px; margin:10px 20px; padding: 20px; border:1px solid #069; border-radius:10px; ';\n" +
		"	displayElapseTime.style.cssText = 'position:absolute; right:20px; top:20px; font-size:64px;';\n" +
		"	document.body.appendChild(_button);\n" +
		"	document.body.appendChild(displayElapseTime);\n\n" +
		"	this.initStartDate = function(){\n" +
		"		startDate = new Date();\n" +
		"	}\n" +
		"	this.clearTimer = function(){\n" +
		"		if(intervalId){\n" +
		"			clearInterval(intervalId);\n" +
		"			intervalId = null;\n" +
		"		}\n" +
		"	}\n" +
		"	this.startTimer = function(){\n" +
		"		_this.clearTimer();\n" +
		"		_this.initStartDate();\n" +
		"		intervalId = setInterval( _this.displayElapsedTime , 100);\n" +
		"	}\n" +
		"	this.displayElapsedTime = function(){\n" +
		"		displayElapseTime.innerHTML = ( (new Date() - startDate) / 1000 ).toFixed(3)\n" +
		"	}\n" +
		"	_button.onclick = function(){\n" +
		"		if(intervalId){\n" +
		"			_this.clearTimer();\n" +
		"		}else{\n" +
		"			_this.startTimer();\n" +
		"		}\n" +
		"	}\n" +
		"}\n" +
		"ElapsedTime();\n" +
		"</script>\n\n" +
		"</body>\n" +
		"</html>\n"
)

func SchulteGrid1() [nCount]int{
	var data [nCount]int;
	source := ring.New(nCount);
	for i := 0; i < nCount; i++ {
		source.Value = i + 1;
		source = source.Next();
	}
	for i := 0; i < nCount; i++ {
		r := rand.Intn(nCount - i);
		source = source.Move(r);
		// for n := 0; n < r; n++ {
		// 	source = source.Next();
		// }
		data[i] = source.Value.(int);
		source = source.Prev();
		source.Unlink(1);
	}
	return data
}

func SchulteGrid2() [nCount]int{
	var source [nCount][2]int;	// 0:n, 1:next
	var data [nCount]int;

	for i := 0; i < nCount; i++ {
		var n = i + 1;
		source[i][0] = n;
		source[i][1] = n;
	}

	current := 0;
	prev := nCount - 1;
	source[prev][1] = current;
	for i := 0; i < nCount; i++ {
		r := rand.Intn(nCount - i);
		for n := 0; n < r; n++ {
			prev = current;
			current = source[current][1];
		}

		data[i] = source[current][0];

		source[prev][1] = source[current][1];
		source[current][1] = -1;
		current = source[prev][1];
	}
	return data
}

func indexHandler(w http.ResponseWriter, r *http.Request){
	w.Header().Set("Content-Type", "text/html; charset=utf-8")

	strHtmlData := "<ul>\n";
	data := SchulteGrid1();
	for i := 0; i < nCount; i++ {
		strHtmlData += "\t<li>" + strconv.Itoa(data[i]) + "</li>\n";
	}
	strHtmlData += "</ul>\n";

	io.WriteString(w, strHtmlDataA)
	io.WriteString(w, strHtmlData)
	io.WriteString(w, strHtmlDataB)
}

func main() {
	http.HandleFunc("/", indexHandler);

	err := http.ListenAndServe(":8080", nil);
	if err != nil {
		log.Fatal("ListenAndServe: ", err.Error());
	}
}
