<h1 align="center">
  <a href="https://www.youtube.com/watch?v=Q7ig6vn-y4M">
    <img src="third_party/clientsocketlib/Youtube.png" alt="유튜브" width="40" style="vertical-align: middle;"/>
  </a>
  <span style="vertical-align: middle;">
    RyomaResourceMonitor
  </span>
</h1>

<p align="center">
  <em>Qt 기반 C++ 데스크탑 앱 — 원격 디바이스 CPU · Memory · Disk 실시간 모니터링</em><br/>
  <sub>Device CRUD(Add/Edit/Delete) · TCP Socket(WinSock2/posix) · Qt Charts · JSON 저장</sub>
</p>

<p align="center">
  <img alt="C++" src="https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B" /></a>
  <img alt="Qt" src="https://img.shields.io/badge/Qt-6-41CD52?logo=qt" /></a>
  <img alt="CMake" src="https://img.shields.io/badge/CMake-build-064F8C?logo=cmake" /></a>
  <img alt="Platform" src="https://img.shields.io/badge/Client-Windows%20x64-black" />
  <img alt="Network" src="https://img.shields.io/badge/Network-TCP-black" />
  <img alt="Storage" src="https://img.shields.io/badge/Storage-JSON-1abc9c" />
  <img src="UI_Image/preview.png" alt="Preview" width="900"/>
</p>

<hr/>

## 목차
- [1. 프로젝트 소개](#1-프로젝트-소개)
- [2. 프로젝트 개요](#2-프로젝트-개요)
- [3. 주요 모듈](#3-주요-모듈) 
- [4. 기술스택](#4-기술스택)
- [5. 참고사항(설치및 사용방법으로)](#5-참고사항설치및-사용방법으로)

---

## 1. 프로젝트 소개
> RyomaResourceMonitor고, 내용은 **서버 자원 가시화 소프트웨어**입니다.

### 무엇을 할 수 있나
- 서버에 CPU,MEMORY,DISK에 사용률을 그래프로 조회 가능

### 기본 사용 흐름(짧게)
1. RyomaResourceMonitor.log 오픈 수정 준비 완료
2. devices.json 로드
3. 아이템 리스트에 장비 추가
4. 장비 접속(Socket 통신 시작)
5. recv 데이터 그래프를 통한 가시화

---

## 2. 프로젝트 개요

### 아키텍처 요약
- **C++ (lib)**: Socket 통신
- **Qt (C++)**: UI

---

## 3. 주요 모듈
### 💻 Client Socket 통신 
**파일:** [libclientsocketlib.a](https://github.com/ryoma-core/cpp-windows-socket-client)  
💡 기능: 소켓 객체를 생성 하여 통신 및 데이터 전달하는 API  
📌 포인트:  
- 소켓 통신
- 데이터 요청

---

### 🖥️ Server Socket 통신
**파일:** [example](https://github.com/ryoma-core/cpp-linux-socket-server)  
💡 기능: 소켓 통신을 통한 전달받은 데이터 타입에 맞추어 서버 자원 파싱 하여 값 Send  
📌 포인트:  
-  서버 자원 파싱
-  데이터 전달
---

### ✅ 장비 리스트 페이지
**파일:** [RyomaResourceMonitor/listpage.h](https://github.com/ryoma-core/RyomaResourceMonitor/blob/main/listpage.h)  
💡 기능: 장비 추가 및 수정,삭제 관리및 연결을 진행  

---

### 📈 모니터링 페이지
**파일:** [RyomaResourceMonitor/monitoringpage.h](https://github.com/ryoma-core/RyomaResourceMonitor/blob/main/monitoringpage.h)
💡 기능: 연결된 서버에 대한 자원 가시화 **C++ (lib)**: Socket 통신  

---

### 🏠 MainWindow (App Root)
**파일:** [RyomaResourceMonitor/mainwindow.h](https://github.com/ryoma-core/RyomaResourceMonitor/blob/main/mainwindow.h)  
💡 기능: 앱의 전체 화면을 관리하는 Window  
📌 포인트:  
- 페이지 전환
- 로그 저장

---

## 4. 기술스택
- C++
- VSCode / Visual Studio 2022 / Qt / CMake

---

## 5. 참고사항(설치및 사용방법으로)
### 🧰 설치및 실행 방법 (Windows)
- **Qt** 설치
- 프로젝트 추가
- 빌드 실행

---

