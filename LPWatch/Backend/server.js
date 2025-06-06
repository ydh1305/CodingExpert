const express = require('express');
const cors = require('cors');
const path = require('path');
const { getTesterData, getHistoryData } = require('./data');

const app = express();
app.use(cors());

// 정적 파일 제공
app.use(express.static(path.join(__dirname, '../frontend')));

// API: 평가 현황
app.get('/api/testers', (req, res) => {
  res.json(getTesterData());
});

// API: 평가 이력
app.get('/api/history', (req, res) => {
  res.json(getHistoryData());
});

// 외부 접속 허용
app.listen(3000, '0.0.0.0', () => {
  console.log(`LPWatch server running at http://12.25.168.177:3000`);
});
