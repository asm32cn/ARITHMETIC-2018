// schulte_grid_demo1_servlet.java

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;


public class schulte_grid_demo1_servlet extends HttpServlet{
	public static final String strAppName = "schulte-grid-demo1-servlet";

	public static final String strHtmlPartA = "<!doctype html>\n" +
		"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n" +
		"<head>\n" +
		"<title>" + strAppName + "</title>\n" +
		"<meta name=\"generator\" content=\"editplus\" />\n" +
		"<style>\n" +
		"body { background-color: #a5cbf7; }\n" +
		"h1 { font-size: 72px; margin:0px; padding:0px; line-height: 150%;}\n" +
		"ul { display:block; margin:0px; padding:0px; float:left; width:500px; height:500px; border-right:1px solid #666; border-bottom:1px solid #666; }\n" +
		"li { display:block; margin:0px; padding:0px; float:left; width:99px; height:99px; line-height: 99px; text-align:center; border-left:1px solid #666; border-top:1px solid #666; font-size:64px; }\n" +
		"#divDisplay { width: 550px; height: 110px; float:left; }\n" +
		"</style>\n" +
		"</head>\n\n" +
		"<body>\n\n" +
		"<h1>" + strAppName + "</h1>\n\n";

	public static final String strHtmlPartB = "<script>\n" +
		"function ElapsedTime(){\n" +
		"\tvar _this = this;\n" +
		"\tvar intervalId = null;\n" +
		"\tvar startDate = null;\n" +
		"\tvar _button = document.createElement('div');\n" +
		"\tvar displayElapseTime = document.createElement('span');\n" +
		"\t_button.innerHTML = 'Start/Stop';\n" +
		"\t_button.style.cssText = 'display:block; float:left; font-size:32px; margin:10px 20px; padding: 20px; border:1px solid #069; border-radius:10px; ';\n" +
		"\tdisplayElapseTime.style.cssText = 'position:absolute; right:20px; top:20px; font-size:64px;';\n" +
		"\tdocument.body.appendChild(_button);\n" +
		"\tdocument.body.appendChild(displayElapseTime);\n" +
		"\n" +
		"\tthis.initStartDate = function(){\n" +
		"\t\tstartDate = new Date();\n" +
		"\t}\n" +
		"\tthis.clearTimer = function(){\n" +
		"\t\tif(intervalId){\n" +
		"\t\t\tclearInterval(intervalId);\n" +
		"\t\t\tintervalId = null;\n" +
		"\t\t}\n" +
		"\t}\n" +
		"\tthis.startTimer = function(){\n" +
		"\t\t_this.clearTimer();\n" +
		"\t\t_this.initStartDate();\n" +
		"\t\tintervalId = setInterval( _this.displayElapsedTime , 100);\n" +
		"\t}\n" +
		"\tthis.displayElapsedTime = function(){\n" +
		"\t\tdisplayElapseTime.innerHTML = ( (new Date() - startDate) / 1000 ).toFixed(3)\n" +
		"\t}\n" +
		"\t_button.onclick = function(){\n" +
		"\t\tif(intervalId){\n" +
		"\t\t\t_this.clearTimer();\n" +
		"\t\t}else{\n" +
		"\t\t\t_this.startTimer();\n" +
		"\t\t}\n" +
		"\t}\n" +
		"}\n" +
		"ElapsedTime();\n" +
		"</script>\n\n" +
		"</body>\n" +
		"</html>\n";

	private final int nCount = 25;

	private int nextInt(int n){
		return (int)(Math.random() * n);
	}

	private List<Integer> getData(){
		List<Integer> list = new ArrayList<Integer>();
		List<Integer> source = new ArrayList<Integer>();
		for(int i = 0; i < nCount; i++){
			source.add(i + 1);
		}
		for(int i = 0; i < nCount; i++){
			int r = nextInt(nCount - i);
			list.add(source.get(r));
			source.remove(r);
		}
		return list;
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
		request.setCharacterEncoding("utf-8");
		response.setCharacterEncoding("utf-8");
		response.setContentType("text/html; charset=utf-8");
		PrintWriter out = response.getWriter();

		List<Integer> data = getData();
		StringBuilder sb = new StringBuilder();
		sb.append("<ul>\n");
		for(int i = 0, l = data.size(); i < l; i++){
			sb.append("\t<li>").append(data.get(i)).append("</li>\n");
		}
		sb.append("</ul>\n");

		out.println(strHtmlPartA);
		out.println(sb.toString());
		out.println(strHtmlPartB);
	} 
}