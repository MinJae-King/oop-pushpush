# PushPush Game (C++)

🧱 **객체지향프로그래밍 (OOP)** 과목 실습 프로젝트  
클래스 기반 구조로 설계된 콘솔 기반의 PushPush 게임입니다.  
사용자는 키보드 입력을 통해 캐릭터를 움직이며 상자를 목표 위치로 밀어넣습니다.

---

## 🛠 기술 스택

- C++17
- 콘솔 출력 기반 UI
- 클래스 기반 구조 (추상화 / 캡슐화 / 다형성 일부 적용)
- 맵 데이터 외부 파일 로드
- 간단한 효과음 재생 (WAV)

---

## 📁 프로젝트 구조

```
OopPushPush/
├── Main.cpp                 // main 함수 및 게임 루프
├── Game.cpp / Game.h       // 게임 전체 흐름 제어
├── Map.cpp / Map.h         // 맵 구조, 이동 가능 여부 판단
├── Renderer.cpp / .h       // 화면 출력 및 그리기
├── KeyboardInput.cpp / .h  // 사용자 입력 처리
├── ActionQueue.cpp / .h    // 입력 큐 및 실행 로직
├── map01.김민재 ~ map05.김민재 // 맵 데이터 파일
├── Sound.wav               // 효과음 (WAV 파일)
└── .gitignore, README.md, ...
```

---

## 🎮 게임 실행 방법

> Windows 환경 기준

### 🔧 컴파일
1. C++17 이상 컴파일러 설치 (예: MinGW, MSVC 등)
2. 프로젝트 루트에서 아래 명령어 실행:

```bash
g++ -std=c++17 -o pushpush Main.cpp Game.cpp Map.cpp Renderer.cpp KeyboardInput.cpp ActionQueue.cpp
```

> 또는 `Makefile` 사용 시 `make` 실행

### ▶ 실행

```bash
./pushpush
```

---

## 📦 기능 요약

- 키보드 입력으로 캐릭터 이동 (`WASD`)
- 상자 밀기 (Push)
- 스테이지 클리어 판정
- 외부 텍스트 기반 맵 로딩
- 효과음 출력 (`Sound.wav`)

---

## 🎓 과제 정보

- **과목명:** 객체지향프로그래밍 (Object-Oriented Programming)
- **제출 연도:** 2023년
- **내용:** 클래스 및 모듈 분리를 통해 게임의 각 기능을 구조적으로 구현

---

## ⚠️ 유의사항

- 콘솔 기반 프로젝트로, 그래픽 라이브러리는 사용하지 않습니다.
- 사운드 재생은 일부 시스템에서 동작하지 않을 수 있습니다.

---

## 🧑‍💻 개발자

- 김민재  
- GitHub: [MinJae-King](https://github.com/MinJae-King)
