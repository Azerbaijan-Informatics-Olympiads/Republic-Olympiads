// ready

// senior only
#import "/templateDay2-AZ.typ": *

#show: project.with(
  title: "Qırılmaz Şəbəkə: Yoxlayıcı",
  time_limit: 1.5,
  memory_limit: 32
)

*Diqqət! Bu məsələdə yaddaş limiti 32 MB-dır.*

Respublika İnformatika Olimpiadasının Yarımfinal mərhələsində iştirakçılara _Qırılmaz Şəbəkə_ adlı məsələ təqdim olunmuşdu. Onların tapşırığı #link("https://algo.az")[`algo.az`] platforması üçün baş şəbəkə mühəndisi rolunda çıxış edərək, $k$ fərqli istehsalçıdan alınan fiber-optik kabellər vasitəsilə $n$ məlumat mərkəzini birləşdirmək idi.

Şəbəkə üçün qoyulan sərt tələb maksimum xətalara davamlılıq idi: əgər hər hansı bir $c$ istehsalçısına aid bütün kabellər qəfil sıradan çıxarsa, yerdə qalan kabellər vasitəsilə şəbəkədəki bütün məlumat mərkəzləri hələ də tam əlaqəli (fully connected) qalmalı idi.

Yarımfinal başa çatdı və minlərlə şəbəkə konfiqurasiyası təqdim olundu. Lakin indi münsiflər heyəti yeni bir problemlə üzləşib: bu nəhəng şəbəkələri səmərəli şəkildə yoxlamaq. Sadə yoxlayıcı proqramlar (checker) ən böyük testləri verilmiş zaman və yaddaş limitləri daxilində emal etmək üçün çox ləngdir.

Sizin tapşırığınız yüksək performanslı yoxlayıcı proqram yazmaqdır. Sizə iştirakçının təqdim etdiyi $n$ məlumat mərkəzi və $m$ kabeldən ibarət şəbəkə verilir. Hər bir kabel istehsalçı nömrəsini bildirən $c$ ilə etiketlənib. $1$-dən $k$-ya qədər hər bir istehsalçı üçün şəbəkənin həmin istehsalçının bütün kabelləri sıradan çıxdığı halda əlaqəli qalıb-qalmadığını müəyyən etməlisiniz.

== Giriş

İlk sətirdə bir tam ədəd $t$ ($1 <= t <= 100$) — testlərin sayı verilir.

Daha sonra hər bir test üçün:

İlk sətirdə üç tam ədəd $n$, $m$ və $k$ ($2 <= n, k <= 250000$; $n-1 <= m <= 250000$) --- uyğun olaraq məlumat mərkəzlərinin, kabellərin və istehsalçıların sayı verilir.

Növbəti $m$ sətrin hər birində üç tam ədəd $u_i, v_i$ və $c_i$ ($1 <= u_i, v_i <= n, u_i != v_i, 1 <= c_i <= k$) verilir. Bu, $u_i$ və $v_i$ məlumat mərkəzlərini birləşdirən və $c_i$ şirkəti tərəfindən istehsal olunan iki tərəfli fiber-optik kabeli təmsil edir.

Zəmanət verilir ki, hər bir test halında verilən ilkin şəbəkə tam əlaqəlidir. Öz-özünə qapanan dövrələr (self-loops) yoxdur, lakin eyni cüt məlumat mərkəzləri arasında birdən çox kabel ola bilər.

Bütün testlər üzrə $n$-lərin cəminin, $m$-lərin cəminin və $k$-ların cəminin ayrı-ayrılıqda 250000-ü aşmadığına zəmanət verilir.

== Çıxış

Hər bir test üçün yalnız `0` və `1` simvollarından ibarət $k$ uzunluqlu bir sətir çap edin. Əgər $i$-ci istehsalçının bütün kabelləri çıxarıldıqdan sonra şəbəkə tam əlaqəli qalırsa, sətrin $i$-ci simvolu `1`, əks halda `0` olmalıdır.

*Qeydlər*

- _Yarımfinalda təqdim olunan Qırılmaz Şəbəkə məsələsinin hər hansı bir detalını xatırlamağınız və ya istifadə etməyiniz tələb olunmur. Həmin məsələyə burada yalnız heykayəyə uyğun olduğu üçün toxunulmuşdur._

- _Bu məsələdə giriş və çıxış verilənləri çox böyükdür. Sürətli giriş-çıxış (I/O) metodlarından istifadə etməyiniz tövsiyə olunur (məsələn, C++ dilində `scanf`/`printf` və ya `cin.tie(0)`/`cout.tie(0)` ilə birlikdə `ios_base::sync_with_stdio(false)`)._

== Məhdudiyyətlər
- $1 <= t <= 100$
- $2 <= n, k <= 250000$ 
- $n-1 <= m <= 250000$
- $sum n, sum m, sum k <= 250000$
- $1 <= u_i, v_i <= n, u_i != v_i$
- $1 <= c_i <= k$
- alt tapşırıqlar üçün qiymətləndirmə bölməsinə baxın.

== Nümunələr

// Input, Output, Explanation
#let examples = (
  (
  "2
3 4 3
1 2 1
1 3 1
2 3 2
1 2 3

3 4 3
1 2 1
1 3 1
2 3 2
2 3 3
",
  
  "111
011",

[- 1-ci testdə, istənilən istehsalçıya aid kabellər sıradan çıxarsa, digər kabellər şəbəkəni tam əlaqəli saxlayır.

- 2-ci testdə, 1 nömrəli istehsalçıya aid kabellər sıradan çıxarsa, 1-ci məlumat mərkəzini birləşdirən bütün kabellər itir və şəbəkə parçalanır. Digər hallarda 1 nömrəli istehsalçıya aid kabellər əlaqəni təmin edir.

Qeyd edək ki, giriş nümunəsində iki test arasında boş sətir testləri rahat fərqləndirə bilməniz üçün əlavə edilmişdir. Real test fayllarında belə boş sətir yoxdur.]
  ),
)

#table(
  columns: (auto, auto, 1fr),
  [*Giriş*], [*Çıxış*], [*İzah*],
  ..examples.map(
    example => (text(example.at(0), font: "Cascadia Code"), text(example.at(1), font: "Cascadia Code"), example.at(2)) 
  ).flatten()
)

#pagebreak()

== Qiymətləndirmə

Bu məsələ aşağıdakı kimi 6 alt tapşırıqdan ibarətdir:

#table(
  align: center,
  columns: (auto, 1fr, 0.5fr),
  [*Alt tapşırıq*], [*Əlavə məhdudiyyətlər*], [*Bal*],
  [0], [Nümunələr], [0 bal],
  [1], [$sum n, sum m, sum k <= 1000$], [12 bal],
  [2], [$n, m, k <= 80000, m = n - 1$], [6 bal],
  [3], [$n, m, k <= 80000, k = m$ və $i$-ci kabelin istehsalçısı $i$-dir], [17 bal],
  [4], [$n, m, k <= 80000, m = n$], [15 bal],
  [5], [$n, m, k <= 80000$], [35 bal],
  [6], [Əlavə məhdudiyyət yoxdur], [15 bal],
)