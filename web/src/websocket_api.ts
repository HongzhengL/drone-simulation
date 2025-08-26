let socket: WebSocket | undefined = undefined;

function sendCommand(command: string, data: any) {
    if (socket && socket.readyState === WebSocket.OPEN) {
        data.command = command;
        socket.send(JSON.stringify(data));
    }
}

function connect(host?: string) {
    const wsProtocol = window.location.protocol === "https:" ? "wss://" : "ws://"; // Detect protocol

    if (host) {
        socket = new WebSocket(`${wsProtocol}${host}`, "web_server");
    } else {
        socket = new WebSocket(`${wsProtocol}${location.host}`, "web_server");
    }

    return new Promise<WebSocket>((resolve, reject) => {
        socket!.onopen = () => {
            resolve(socket!);
        };

        socket!.onerror = (error) => {
            console.error("WebSocket connection error:", error);
            reject(error);
        };
    });
}

function disconnect() {
    if (socket) {
        socket.close();
    }
}

export { connect, disconnect, sendCommand };

