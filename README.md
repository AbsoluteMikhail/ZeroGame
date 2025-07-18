# Zero Game

## Простой сетевой шутер от первого лица
Изначально разработано на UE 5.2 и C++ (обновлено до UE 5.6, см. теги)
<br/>*В версии 5.6 нужно перейти на [SteamSockets](https://dev.epicgames.com/documentation/en-us/unreal-engine/using-steam-sockets-in-unreal-engine)

Используется плагин [AdvancedSteamSessions](https://vreue4.com/advanced-sessions-binaries)
<br/>*(обновляя движок не забуть обновить плагин в папке проекта)*

В сборку игры нужно положить steam_appid.txt примерно туда *"Сборка\Название_игры\Binaries\Win64"*.
<br/>*(стим будет работать только в шипинг билде)*

### Скачать игру:
Можно [с облака](https://cloud.mail.ru/public/mfHp/5riKVomkB)
<br/>👇 Видео геймплея доступно на YouTube 👍
<br/>[![Видео геймплея тут](https://img.youtube.com/vi/W9m85_skCCo/0.jpg)](https://cloud.mail.ru/public/5AJu/vEWPsYhrY)

*инфа ниже устарела походу =)
<br/>Обязательно закинь DLL из папки стима в папку движка
<br/>(Примерно отсюда *C:\Program Files (x86)\Steam*, примерно сюда *Папка_UE\Engine\Binaries\ThirdParty\Steamworks\Steamv153\Win64*)
- steamclient64.dll
- tier0_s64.dll
- vstdlib_s64.dll

<br/>Основано на
[Инструкция дедов 1](https://devtribe.ru/p/unreal-engine/27-05-2019-vnedrenie-steamworks-sdk-v-unreal-engine), [Инструкция дедов 2](https://itch.io/blog/641002/advanced-steam-sessions-multiplayer-unreal-engine-tutorial)

<!--
Ссылка на ролик на ютубе: https://www.youtube.com/watch?v=W9m85_skCCo

Документация по форматированию: 
https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax
-->
