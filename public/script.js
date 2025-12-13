// 当前用户（简化版，实际应该用 session/cookie）
let currentUser = 'testuser';

// 加载航班列表
async function loadFlights() {
    try {
        const response = await fetch('/api/flights');
        const flights = await response.json();
        
        const tbody = document.querySelector('#flightTable tbody');
        tbody.innerHTML = '';

        flights.forEach(flight => {
            const tr = document.createElement('tr');
            tr.innerHTML = `
                <td>${flight.id}</td>
                <td>${flight.from}</td>
                <td>${flight.to}</td>
                <td>¥${flight.price}</td>
                <td>剩余 ${flight.seats} 座</td>
                <td>
                    <button onclick="book('${flight.id}')" 
                            ${flight.seats === 0 ? 'disabled' : ''}>
                        ${flight.seats === 0 ? '已售罄' : '订票'}
                    </button>
                </td>
            `;
            tbody.appendChild(tr);
        });

    } catch (error) {
        console.error('获取航班失败:', error);
        alert("❌ 无法连接到服务器！");
    }
}

// 订票
async function book(flightId) {
    if (!confirm(`确认订票 ${flightId} 吗？`)) {
        return;
    }

    try {
        const response = await fetch('/api/book', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                flightId: flightId,
                username: currentUser
            })
        });

        const result = await response.json();
        
        if (response.ok) {
            alert(`✅ ${result.message}\n订票号: ${result.ticketId}`);
            loadFlights(); // 刷新列表
        } else {
            alert(`❌ ${result.error}`);
        }

    } catch (error) {
        console.error('订票失败:', error);
        alert("❌ 订票请求失败！");
    }
}

// 查看我的订单
async function loadMyTickets() {
    try {
        const response = await fetch(`/api/tickets?username=${currentUser}`);
        const tickets = await response.json();
        
        if (tickets.length === 0) {
            alert("你还没有订票记录");
            return;
        }

        let message = "📋 我的订单：\n\n";
        tickets.forEach((ticket, index) => {
            message += `${index + 1}. 订票号: ${ticket.ticketId}\n`;
            message += `   航班号: ${ticket.flightId}\n`;
            message += `   价格: ¥${ticket.price}\n\n`;
        });
        
        alert(message);

    } catch (error) {
        console.error('获取订单失败:', error);
        alert("❌ 无法获取订单！");
    }
}

// 退票
async function cancelTicket() {
    const ticketId = prompt("请输入要退票的订票号:");
    if (!ticketId) return;

    try {
        const response = await fetch('/api/cancel', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                ticketId: ticketId
            })
        });

        const result = await response.json();
        
        if (response.ok) {
            alert(`✅ ${result.message}`);
            loadFlights(); // 刷新列表
        } else {
            alert(`❌ ${result.error}`);
        }

    } catch (error) {
        console.error('退票失败:', error);
        alert("❌ 退票请求失败！");
    }
}

// 页面加载完成后自动执行
window.onload = loadFlights;