function getTesterData() {
  const testers = [];
  for (let i = 1; i <= 6; i++) {
    testers.push({
      id: `APTester-${i}`,
      input: 100,
      pass: Math.floor(Math.random() * 90),
      fail: Math.floor(Math.random() * 10),
    });
  }
  return {
    apTesters: testers,
    apHandlers: Array.from({ length: 6 }, (_, i) => `APHandler-${i + 1}`)
  };
}

function getHistoryData() {
  return [
    { month: '2025-01', count: 12 },
    { month: '2025-02', count: 9 },
    { month: '2025-03', count: 15 },
    { month: '2025-04', count: 11 },
    { month: '2025-05', count: 13 },
  ];
}

module.exports = { getTesterData, getHistoryData };
