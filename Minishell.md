# Minishell
## shell 만큼 아름답다
요약: 이 과제의 목표는 여러분이 간단한 셸을 만들게 하는 것입니다. 네, 여러분의 작은 bash나 zsh 입니다. 여러분은 프로세스와 파일 디스크립터에 대해 많이 배울 것입니다.

# 목치
1. 소개
2. 일반 사항
3. 필수 파트
4. 보너스 파트

# 제1 장
## 소개
셸의 존재는 IT의 존재와 관련이 있습니다. 당시 모든 코더들은 정렬 된 1/0 스위치를 사용하여 컴퓨터와 통신하는 것이 심각하게 화나게 하는 일이라는 것에 동의했습니다. 영어에 가까운 명령행으로 컴퓨터와 소통한다는 생각을 해낸 것은 당연한 수순이었습니다.

Minishell로, 여러분은 시간을 거슬러 윈도우즈가 존재하지 않아서 사람들이 문제를 겪던 시절로 여행하고 올 것입니다.

# 제2 장
## 기본 사항
- 여러분의 프로젝트는 Norm 규약에 맞춰 쓰여야 합니다. 보너스 파일/함수가 있다면, norm체크에 포함될 것이고, norm 에러가 발생하면 0점을 받게 됩니다.
- 여러분의 함수가 정의되지 않은 동작과는 별개로 예기치 못하게 종료(segmentation fault, bus error, double free 등)되어서는 안 됩니다. 발생한다면 여러분의 프로제트는 함수 없음으로 간주되고 평가에서 0점을 받게 됩니다.
- 모든 할당된 메모리는 적절하게 해제되어야 합니다. 어떠한 누수도 용납되지 않습니다.
- 과제에 필요하다면, 소스 파일을 -Wall -Wextra -Werror 플래그로 컴파일 하여 결과물을 내는 Makefile을 제출해야 하고, 여러분의 Makefile은 리링크해서는 안 됩니다.
- 여러분의 Makefile은 적어도 $(NAME), all, clean, fclean 및 re 룰을 포함하고 있어야 합니다.
- 보너스를 제출하려면, Makefile에 보너스 룰을 포함시키고, 프로젝트의 주요 파트에서는 금지되었던 여러 헤더, 라이브러리나 함수를 추가합니다. 보너스는 반드시 _bonus.{c/h}로 다른 파일이어야 합니다. 필수파트와 보너스파트는 각각 평가될 것입니다.
- 여러분의 프로젝트가 libft 사용을 허락한다면, 여러분은 반드시 libft 폴더에 그 소스를 복사하고 관련된 Makefile을 두어야 합니다. 여러분의 프로젝트의 Makefile이 libft의 Makefile을 이용해서 라이브러리를 컴파일 해야 하고, 그런 다음 프로젝트를 컴파일 합니다.
- 제출되지 않고 평가받지도 않겠지만, 테스트 프로그램을 만들어볼 것을 권합니다. 동료평가를 수월하게 해 줄 것입니다. 여러분은 이런 테스트가 특히 여러분의 디펜스에 유용하다는 것을 알게 될 것입니다. 게다가 디펜스 하는 동안 여러분은 테스트를 편하게 써도 되고, 동료를 평가해 줄 때에도 마찬가지 입니다.
- 여러분에게 할당된 깃 저장소에 제출하세요. 깃 저장소에 있는 작업물만 평가될 것입니다. Deepthought이 여러분의 과제 평가에 할당되면, 여러분의 동표평가 후에 Deepthought가 평가를 마칠 것입니다. Deepthought가 평가하는 도중에 어느 부분에서든 오류가 발생한다면 평가는 중단됩니다.

# 제3 장
## 필수 파트
- 프로그램 명: minishell
- 제출 파일:
- Makefile: Yes
- 인자:
- 외부 함수:
	- malloc, free, write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno
- Libft 허가: Yes
- 할일: 셸 작성

여러분의 셸은 이러해야 합니다:
- 새로운 명령을 기다릴 때 프롬프트를 보여줍니다.
- bash에서와 같이 올바른 실행 파일을 검색하고 실행하십시오 (PATH 변수 기반 또는 상대 또는 절대 경로 사용)
- bash와 같이 내장을 구현해야합니다.
	- echo : 옵션 '-n'
	- cd : 상대 또는 절대 경로
	- pwd : 옵션 없이
	- export : 옵션 없이
	- unset : 옵션 없이
	- env : 옵션과 인수 없이
	- exit :옵션 없이
- 명령에 ;이 있으면 bash에서처럼 명령을 나누기
- ' 과 "는 여러 행 명령을 제외하고는 bash에서처럼 작동해야 합니다.
- < > ">>" 리다이렉션은 파일디스크립터 집계를 제외하고는 bash에서처럼 작동해야 합니다.
- 파이프 |는 bash에서처럼 작동해야 합니다.
- 환경변수들($뒤에 오는 문자들)은 bash에서처럼 작동해야 합니다.
- $?는 bash에서처럼 작동해야 합니다.
- ctrl-C, ctrl-D, ctrl-\는 bash와 같은 결과를 내야 합니다.

# 제4 장
## 보너스 파트
- 필수파트가 완벽하지 않다면 보너스는 생각도 마세요.
- 모든 보너스를 할 필요는 없답니다.
- "<<"를 bash처럼 리다이렉션
- Termcaps를 사용한 히스토리 및 라인 편집 (man tgetent 예)
	- 커서가 있는 곳의 라인을 편집하십시오.
	- 커서를 오른쪽 왼쪽으로 움직여서 행의 특정 위치를 수정할 수 있게 하십시오. 클래식 셸처럼 명백하게 새로운 글자는 존재하는 것들 사이에 삽입되어야 합니다.
	- 위아래 화살표로 커맨드 히스토리를 탐색하고, 히스토리는 우리가 원한다면 수정할 수 있습니다. (히스토리가 아니고 명령행)
	- 원하는 키 시퀀스로 라인의 일부 또는 전부를 cut, copy, paste 합니다.
	- ctrl + LEFT나 ctrl + RIGHT로 단어 왼쪽이나 오른쪽으로 바로 이동합니다.
	- home이나 end를 눌러서 라인의 처음이나 끝으로 바로 이동하기
	- Write AND edit a command over a few lines. In that case, we would love that ctrl+UP and ctrl+DOWN allow to go from one line to another in the command while remaining in the same column or otherwise the most appropriate column.
- bash에서처럼 &&, || 괄호를 통한 우선순위
- bash에서처럼 와일드카드 *


# 테스트케이스
순한맛
echo '$USER'			//	$USER
echo "$USER"			//	minckim 
echo "'$USER'"			//	'minckim'
echo '"$USER"'			//	"$USER"
echo ''$USER''			//	minckim
echo '''$USER'''		//	$USER
echo "'''""''a''""'''"	//	'''''a'''''
echo $USER=aaa			//	minckim=aaa
echo $HELLO=aaa			//	=aaa
echo "hello\nman"		//	hello\nman
echo hello\nman			//	hellonman
echo "hello\ man"		//	hello\ man
echo "hello'man"		//	hello'man
echo "hello'man\""		//	hello'man"
echo 'hello"man'		//	hello"man

약간매운맛
echo aa"bb$USER"cc		//	aabbminckimcc
echo aa"bb$USER cc"dd	//	aabbminckim ccdd
echo aa"bb$USERcc"dd	//	aabbdd
echo 'qqq\'				//	qqq\
export aa=bb=cc			//	env=> aa=bb==cc
echo "hello$USER_"		//	hello

매운맛
ec"""ho""" hello		//	hello
ec"ho" hello			//	hello
ec'ho' hello			//	hello
ec"'ho'" hello			//	bash: ec'ho': command not found

핵불닭볶음면맛
echo hello '|' grep h	//	hello | grep h

# 평가표
## 필수파트

### 간단한 명령
- 절대경로로 아무 옵션 없이 /bin/ls 등의 간단한 명령을 실행해 보세요. 

### 인자
- 절대경로로 인자는 포함하되 따옴표 없이 /bin/ls 등의 간단한 명령을 실행해 보세요.
- 다른 명령과 인자로 여러번 반복해 보세요.

### echo
- echo 명령을 인자나 옵션 없이 실행해 보세요.
- 다른 인자로 여러번 반복해 보세요.

### exit
- exit 명령을 인자나 옵션 없이 실행해 보세요.
- 다른 인자로 여러번 반복해 보세요.
- minishell을 재실행하는 것을 잊지 마세요.

### 프로세스의 리턴 값
- 절대경로로 인자는 포함하되 따옴표 없이 /bin/ls 등의 명령을 실행하고 echo $? 를 실행해 보세요.
- 출력되는 결과를 확인하세요. 여러분은 배시에서 똑같이 반복하고 비교해 볼 수 있습니다.
- 다른 명령어와 인자로 여러번 반복해 보고, '/bin/ls filethatdoesntexist'처럼 실패하는 명령어를 사용해 보세요.

### 세미콜론
- 절대경로로 인자를 포함하되 세미콜론으로 분리된 여러개의 명령을 실행해 보세요.
- 다른 명령을 여러번 반복하되 세미콜론 주변을 공백으로 감싸거나 감싸지 않는 것을 잊지 마세요.

### 시그널
- 빈 프롬프트에서 ctrl-C
- 빈 프롬프트에서 ctrl-\
- 빈 프롬프트에서 ctrl-D
- 무언가 입력한 프롬프트에서 ctrl-C
- 무언가 입력한 프롬프트에서 ctrl-D
- 무언가 입력한 프롬프트에서 ctrl-\
- cat이나 grep 처럼 blocking 명령 다음에 ctrl-C
- cat이나 grep 처럼 blocking 명령 다음에 ctrl-D
- cat이나 grep 처럼 blocking 명령 다음에 ctrl-\
- 다른 명령으로 여러번 해보기

### 큰따옴표
- 절대경로로 간단한 명령을 실행해보되, 이번에는 큰따옴표로 해보기(따옴표 사이에 공백과 세미콜론을 포함해야 합니다)
- 빈 인자나 '\'를 이상하게 쓰는 것도 생각해 보세요.
- 여러 행을 시도하지 마세요.

### env
- env가 여러분에게 현재 환경변수를 보여주는지 확인하세요.

### export
- 환경변수를 내보내고, 새로운 것을 만들고 옛 것을 교체해보세요.
- env로 비교해 보세요.

### unset
- 환경변수를 내보내고, 새로운 것을 만들고 옛 것을 교체해보세요. 
- unset으로 그것 들 중 몇 개를 제거해 보세요.
- env로 결과를 확인해보세요.

### 환경변수
- echo를 $ 변수 몇 개를 인자로 실행해 보세요.
- 큰따옴표로 감싼 $ 변수들이 잘 작동하는지 확인해 보세요(배시에서 처럼)

### cd
- cd 명령을 써서 작업 디렉토리를 옮기고, 올바른 디렉토리에 있는지 /bin/ls로 확인해 보세요.
- 작동하거나 작동하지 않는 cd를 여러번 해보세요.
- '.' '..' 인자도 해보세요.

### pwd
- pwd 명령을 사용해 보세요.
- 여러 디렉토리에서 여러번 반복해 보세요.
- '.' '..' 인자도 해보세요.

### 상대경로
- 이번에는 상대경로로 명령을 실행해 보세요.
- 복잡한 경로로 여러 디렉토리에서 여러번 반복해 보세요. (.. 여러개)

### 환경변수 경로
- 이번에는 경로 없이 명령을 실행해 보세요. (ls, wc, awk, etc...)
- $PATH를 unset하고 더이상 작동하지 않는지 확인해보세요.
- $PATH를 여러 디렉토리 변수(directory1:directory2)로 설정하고 디렉토리를 왼쪽에서 오른쪽 순으로 확인하는 확인해보세요.

### 간단한 작은따옴표
- 간단한 작은따옴표로 된 변수를 실행해 보세요.
- 빈 변수로 해보세요.
- 환경변수, 공백, 세미콜론으로 해보세요.

### 리다이렉션
- <나 > 리다이렉션으로 명령을 실행해 보세요.
- 다양한 명령과 인자로 여러번 반복하고, 가끔 >를 >>로 바꿔보세요.
- 여러번 똑같은 리다이렉션이 실패하는지 확인해보세요.



**Redirection**
\- Execute commands with redirections < and/or >
\- Repeat multiple times with different commands and arguments and sometimes change > with >>
\- Check if multiple of the same redirections fail
 Yes
 No
**Pipes**
\- Execute commands with pipes like 'cat file | grep bla | more'
\- Repeat multiple times with different commands and arguments
\- Try some failing commands like 'ls filethatdoesntexist | grep bla | more'
\- Try to mix pipes and redirections.
 Yes
 No
**Go Crazy**
\- Execute commands that should not work like 'dsbksdgbksdghsd' and check if the shell doesn't crash and prints an error
\- Try to execute a really really really long command with a ton of arguments
\- Have fun with that beautiful minishell and enjoy it
 Yes



 
 NoBonus
*We will look at your bonuses if and only if your mandatory part is excellent. This means that you must complete the mandatory part, beginning to end, and your error management must be flawless, even in cases of twisted or bad usage. So if you didn't score all the points on the mandatory part during this defence bonuses will be totally ignored.*
**double left redirection**
\- Check if << is working fine
 Yes
 No
**Line editing**
\- Can we move the cursor left and right and edit the line by inserting or deleting characters at cursor location
\- Can we navigate through history with up and down
\- Can we copy paste all/part of a line using a key sequence
\- Can we move word by word with ctrl+left or ctrl+right
\- Go directly to the beginning or the end of the line with home or end
\- Write and edit commands with multilines
**Rate it from 0 (failed) through 5 (excellent)**A**nd, Or**
\- Use &&, || and parenthesis with commands and check if it works like bash
\- For each working flag give 1 point
\- If all flags are working give 1 bonus point
 Yes
 No
W**ildCard**
\- Use wildcards in arguments
\- Try things like */*
\- Go crazy with wildcards