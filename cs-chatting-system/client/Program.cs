// EchoClient.cs
using System;
using System.Net.Sockets;
using System.Text;

class EchoClient
{
    static void Main()
    {
        try
        {
            TcpClient client = new TcpClient("127.0.0.1", 12345); // 서버 주소
            NetworkStream stream = client.GetStream();

            Console.Write("보낼 메시지 입력: ");
            string message = Console.ReadLine();

            byte[] data = Encoding.UTF8.GetBytes(message);
            stream.Write(data, 0, data.Length);

            byte[] response = new byte[1024];
            int bytes = stream.Read(response, 0, response.Length);
            Console.WriteLine("서버 응답: " + Encoding.UTF8.GetString(response, 0, bytes));

            stream.Close();
            client.Close();
        }
        catch (Exception ex)
        {
            Console.WriteLine("오류: " + ex.Message);
        }
    }
}
