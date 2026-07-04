# Zero Game

Автор: [Absolute Mikhail](https://absolutemikhail.github.io)

## Простой сетевой шутер от первого лица
Изначально разработано на UE 5.2 и C++
<br/>(см. теги на git для выбора коммита с нужной версией)
<br/>В каждой версии АБСОЛЮТНО точно работает соединение через стим, я проверял =)

<br/>Начиная с версии 5.6+ нужно перейти на [SteamSockets](https://dev.epicgames.com/documentation/en-us/unreal-engine/using-steam-sockets-in-unreal-engine)
<br/>Используется плагин [AdvancedSteamSessions](https://vreue4.com/advanced-sessions-binaries)
<br/>*(обновляя движок не забуть обновить плагин в папке проекта)*

> [!NOTE]
> Текущий конфиг проекта настроен под Steam/SteamSockets: `DefaultPlatformService=Steam` и `SteamSocketsNetDriver`.
> Для обычного поиска игры в локальной сети без Steam нужно переключить проект на `OnlineSubsystemNull` и стандартный `IpNetDriver`, а при создании/поиске сессии включить LAN-режим.
>
> Пример LAN-настроек в `Config/DefaultEngine.ini`:
> ```ini
> [/Script/Engine.GameEngine]
> !NetDriverDefinitions=ClearArray
> +NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="/Script/OnlineSubsystemUtils.IpNetDriver",DriverClassNameFallback="/Script/OnlineSubsystemUtils.IpNetDriver")
>
> [OnlineSubsystem]
> DefaultPlatformService=Null
>
> [OnlineSubsystemNull]
> bEnabled=true
> ```
>
> В Blueprint/AdvancedSessions для LAN также должны совпадать настройки создания и поиска: `Use LAN = true`, а серверная карта должна открываться с параметром `?listen`.

В сборку игры нужно положить steam_appid.txt примерно туда *"Сборка\Название_игры\Binaries\Win64"*.
<br/>*(стим будет работать только в шипинг билде!)*

*При настройке своего проекта, обрати внимание что GameInstance наследуется от UAdvancedFriendsGameInstance

### Скачать игру:
Можно [с облака](https://cloud.mail.ru/public/mfHp/5riKVomkB)
<br/>👇 Видео геймплея доступно на YouTube 👍
<br/>[![Видео геймплея тут](https://img.youtube.com/vi/W9m85_skCCo/0.jpg)](https://cloud.mail.ru/public/5AJu/vEWPsYhrY)

*инфа ниже устарела походу для версий старше 5.2
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


### Лицензия
Проект опубликован как учебный пример и портфолио. Собственный код можно смотреть, форкать, изучать, менять и использовать в некоммерческих учебных проектах с сохранением копирайта и ссылки на лицензию.

Ассеты Unreal Engine, Starter Content, First Person/Third Person template content и похожие материалы Epic Games не принадлежат мне и остаются под лицензиями Epic Games/Unreal Engine EULA.

Плагины AdvancedSessions и AdvancedSteamSessions тоже не мои. Они используются только для демонстрации Steam multiplayer setup и остаются под условиями своих авторов.

Подробнее см. [LICENSE](LICENSE).
