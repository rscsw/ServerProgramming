using System.Net;

HttpListener listener = new HttpListener();
listener.Prefixes.Add("http://127.0.0.1:3000/JennyHoon/"); //RestAPI는 꼭 슬래쉬 / 로 끝내줘야한다
listener.Start();
Console.WriteLine("Listening...");

HttpListenerContext context = listener.GetContext(); //http listener 객체
HttpListenerRequest request = context.Request; //응답을 받는 것
HttpListenerResponse response = context.Response; //응답을 보내는 것
Stream body = request.InputStream;
System.Text.Encoding encoding = request.ContentEncoding;
System.IO.StreamReader reader = new System.IO.StreamReader(body, encoding);
string s = reader.ReadToEnd();
string responseString = "<html><body>S loves J "+s+"</body></html>";
Console.WriteLine(responseString);
byte[] buffer = System.Text.Encoding.UTF8.GetBytes(responseString);
response.OutputStream.Write(buffer, 0, buffer.Length); //버퍼, 오프셋(보낼 버퍼의 시작점), 카운트(보낼 버퍼의 길이)
response.OutputStream.Close();
listener.Stop();