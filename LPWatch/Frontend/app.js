function navigate(page) {
  const content = document.getElementById('content');
  content.innerHTML = '';

  if (page === 'home') {
    content.innerHTML = `
      <h1>LPWatch 품질 포털</h1>
      <p>품질 테스트 부서 전용 포털 사이트입니다. 12대의 설비 상태를 실시간으로 확인하고, 이력 관리를 할 수 있습니다.</p>
    `;
  }

  if (page === 'status') {
    content.innerHTML = `<h2>설비 평가 현황</h2><div id="tester-charts"></div><canvas id="summaryChart"></canvas>`;
    fetch('/api/testers')
      .then(res => res.json())
      .then(data => {
        const testerCharts = document.getElementById('tester-charts');
        let totalInput = 0, totalPass = 0, totalFail = 0;

        data.apTesters.forEach((tester, index) => {
          const remaining = tester.input - tester.pass - tester.fail;
          totalInput += tester.input;
          totalPass += tester.pass;
          totalFail += tester.fail;

          const canvas = document.createElement('canvas');
          canvas.id = `testerChart${index}`;
          testerCharts.appendChild(canvas);

          new Chart(canvas, {
            type: 'bar',
            data: {
              labels: ['Input', 'Pass', 'Fail', 'Remain'],
              datasets: [{
                label: tester.id,
                data: [tester.input, tester.pass, tester.fail, remaining],
                backgroundColor: ['#3498db', '#2ecc71', '#e74c3c', '#95a5a6']
              }]
            },
            options: { responsive: true }
          });
        });

        // 전체 요약 차트
        const ctx = document.getElementById('summaryChart');
        new Chart(ctx, {
          type: 'pie',
          data: {
            labels: ['총 Pass', '총 Fail', '총 잔여'],
            datasets: [{
              data: [totalPass, totalFail, totalInput - totalPass - totalFail],
              backgroundColor: ['#2ecc71', '#e74c3c', '#95a5a6']
            }]
          },
          options: { responsive: true }
        });
      });
  }

  if (page === 'history') {
    content.innerHTML = `<h2>평가 이력 (월별)</h2><canvas id="historyChart"></canvas>`;
    fetch('/api/history')
      .then(res => res.json())
      .then(data => {
        const ctx = document.getElementById('historyChart');
        new Chart(ctx, {
          type: 'line',
          data: {
            labels: data.map(e => e.month),
            datasets: [{
              label: '월별 평가 건수',
              data: data.map(e => e.count),
              borderColor: '#2980b9',
              fill: false
            }]
          },
          options: { responsive: true }
        });
      });
  }
}

// 기본 페이지 로딩
navigate('home');
