// 这个函数负责向 C++ 后端要数据
async function loadFlights() {
    try {
        // 发送请求给 C++ (对应 Server.cpp 里的 /api/flights)
        const response = await fetch('/api/flights');
        
        // 解析 C++ 返回的 JSON 字符串
        const flights = await response.json();
        
        // 拿到表格身体部分
        const tbody = document.querySelector('#flightTable tbody');
        tbody.innerHTML = ''; // 清空旧数据

        // 遍历数据，生成 HTML
        flights.forEach(flight => {
            const tr = document.createElement('tr');
            tr.innerHTML = `
                <td>${flight.id}</td>
                <td>${flight.from}</td>
                <td>${flight.to}</td>
                <td>¥${flight.price}</td>
                <td><button onclick="book('${flight.id}')">订票</button></td>
            `;
            tbody.appendChild(tr);
        });

    } catch (error) {
        console.error('获取航班失败:', error);
        alert("无法连接到服务器！");
    }
}

function book(flightId) {
    alert("你点击了订票: " + flightId + " (功能待后端连接)");
    // 这里可以使用 fetch 发送 POST 请求给 /api/book
}

// 页面加载完成后自动查一次
window.onload = loadFlights;