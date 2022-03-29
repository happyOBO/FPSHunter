## FPS Hunter

- [데모 영상](https://youtu.be/fa939ckr2kM)
- 숲속에서 사냥하는 게임
- 사냥한 동물을 갈무리하면 코인을 얻을 수 있다.

---

### 컨텐츠

#### 동물 컨텐츠

- [x] 동물 BP 만들기
    - [x] 체력
    - [x] 죽는 애니메이션
    - [x] 공격 당했을 때 체력 감소
- [x] AI
- [x] 사슴
- [x] 여우
- [x] 늑대

#### 총기 컨텐츠

- [x] 동물에 닿으면 터지는 효과 추가
- [x] 동물에 닿으면 총알 사라지게
- [x] 총 교체 가능
- [x] Projectile (오버워치 메이)
    - [x] 튀기기 X
    - [x] 작은 총알
    - [x] 속도가 빠르고 휘는 느낌이 적어야함.

- [x] Arc Projectile (오버워치 정크렛)
    - [x] 좀 덜 튀기게
    - [x] 큰 총알 투포환 느낌
    - [x] 시간이 지나서 사라질 때도 터지고 사라지는 효과 추가

- [x] Weapon 액터 추가, 프로젝타일, 웨폰 메쉬 갖고 있음

#### 기타 컨텐츠

- [x] 갈무리 기능
- [x] UI
    - [x] 총 교체 UI
    - [x] 코인


---

### 커밋 로그


#### Commits on Mar 29, 2022
- 세부 값 조절
- 숲 맵 에셋에 적용
- 갈무리 기능 및 코인 추가
- 장전 끝난후에 탄환 충전 및 탄환 없으면 발사 사운드 안나게끔 수정
- 장전 기능 추가
- 탄환 수 UI 추가
- Weapon 액터 추가


 
#### Commits on Mar 28, 2022

- Weapon 변경 UI 추가
- 무기 에셋 추가 및 무기 변경 시 무기 메시 변경

 
#### Commits on Mar 25, 2022

- 마우스 휠로 무기 변경
 
#### Commits on Mar 24, 2022

- 사슴 , 늑대 추가
- 죽으면 안움직이게끔 (AI friend class 로 선언)
- FOX Rotation 변경
- Fox Animation Blender 추가

#### Commits on Mar 23, 2022

- Fox AI 추가
- Projectile & Arc Projectile 생성
- 시간이 지나서 사라질 때 처리 (LifeSpanExpired() 오버라이딩)
- 파일 정리 및 폭발 이펙트 추가
- plugin 라이브러리 임포트 오류 해결


#### Commits on Mar 22, 2022

- HeadMountedDisplay --> Niagara & VR 용 코드 제거
- 숲 에셋 추가 ( 용량 부족으로 깃헙에는 올리지 않음)
- 죽은 애니메이션 유지 (Auto Blend Out X)
- fox Dead Montage 추가
- FOX 애니메이션 Blueprint 추가
- FPSHunterMammal 추가 : 공격, 체력 감소
- Animal 에셋 폴더 정리

#### Commits on Mar 21, 2022

- Animal 에셋 추가
