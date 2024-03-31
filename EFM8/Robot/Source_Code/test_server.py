import socket

def start_server():
    host = '0.0.0.0'  # Listen on all network interfaces
    port = 12345  # Port number to listen on

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        print(f"Server listening on port {port}...")
        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr}")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(f"Received: {data.decode('utf-8')}")
                conn.sendall(b"Echo: " + data)

if __name__ == "__main__":
    start_server()
