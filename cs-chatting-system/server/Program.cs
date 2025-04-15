// EchoServer.cs
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class EchoServer
{
    static void Main()
    {
        TcpListener listener = new TcpListener(IPAddress.Any, 12345);
        listener.Start();
        Console.WriteLine("서버 실행 중... 클라이언트 대기 중");

        while (true)
        {
            TcpClient client = listener.AcceptTcpClient();
            Console.WriteLine("클라이언트 연결됨");

            NetworkStream stream = client.GetStream();
            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = stream.Read(buffer, 0, buffer.Length)) > 0)
            {
                string received = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                Console.WriteLine("받은 메시지: " + received);

                // 그대로 되돌려 보냄 (에코)
                stream.Write(buffer, 0, bytesRead);
            }

            Console.WriteLine("클라이언트 연결 종료");
            client.Close();
        }
    }
}
