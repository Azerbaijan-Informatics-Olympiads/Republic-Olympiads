// ready

// junior only
#import "/templateDay2-AZ.typ": *

#show: project.with(
  title: "Ən Yaxın Ortaq Əcdad (LCA)",
  time_limit: 1,
  memory_limit: 256
)

Sizə $n$ təpəsi olan ağac, yəni dövrü olmayan, əlaqəli, istiqamətlənməmiş qraf verilir. Ağacın kökü 1 nömrəli təpədir.

Ağacın iki təpəsi arasındakı məsafə həmin təpələr arasındakı yolda olan tillərin sayına bərabərdir.

Ağacın təpələrindən ibarət, boş olmayan, hər hansı $U = {u_1, u_2, ..., u_k}$ çoxluğuna baxaq. Bu çoxluğun _ən yaxın ortaq əcdadı_ hər bir $u_i in U$ üçün 1 nömrəli təpədən $u_i$-yə gedən yolun üzərində olan və 1 nömrəli təpədən ən uzaqda yerləşən təpədir.

Hər bir boş olmayan təpələr çoxluğu üçün həmin çoxluğun ən yaxın ortaq əcdadı olan təpəni nəzərə alın. Bu təpələrin indekslərinin cəmini tapın. Bu cəm çox böyük ola bilər, ona görə də siz bu cəmin $998244353$-ə qalığını çıxışa verməlisiniz.

== Giriş

Girişin birinci sətrində bir tam ədəd $n$ ($1 <= n <= 3 dot 10^5$) — ağacdakı təpələrin sayı verilir.

Növbəti $n - 1$ sətrin hər birində iki tam ədəd $u_i$ və $v_i$ ($1 <= u_i, v_i <= n$) verilir, onlar $u_i$ və $v_i$ təpələri arasındakı tili təsvir edir. Verilən qrafın ağac olduğuna zəmanət verilir.

#linebreak()

_*Qeyd:*  Bu məsələdə giriş verilənləri çox böyükdür. Sürətli giriş-çıxış (I/O) metodlarından istifadə etməyiniz tövsiyə olunur (məsələn, C++ dilində `scanf`/`printf` və ya `cin.tie(0)`/`cout.tie(0)` ilə birlikdə `ios_base::sync_with_stdio(false)`)._

== Çıxış

Bir tam ədəd — tələb olunan cəmin $998244353$-ə qalığını çıxışa verin. 
 
== Məhdudiyyətlər
- $1 <= n <= 3 dot 10^5$
- $1 <= u_i, v_i <= n$
- alt tapşırıqlar üçün qiymətləndirmə bölməsinə baxın.

#pagebreak()

== Nümunələr

// Input, Output, Explanation
#let examples = (
  (
  "4
1 2
2 3
2 4
",
  
  "25",

[Əgər 1 təpəsi $U$ çoxluğuna daxildirsə, $U$-nun ən yaxın ortaq əcdadı 1-dir, çünki 1-dən bu təpəyə olan yol yalnız 1-dən ibarətdir. Belə səkkiz çoxluq var.

Əgər 1 təpəsi $U$ çoxluğuna daxil deyilsə, lakin 2 daxildirsə, $U$-nun ən yaxın ortaq əcdadı 2-dir, çünki bütün yollar 1 və 2 təpələrini ehtiva edir və 2 təpəsi 1 təpəsindən (kökdən) 1 təpəsinə nisbətən daha uzaqdadır. Belə dörd çoxluq var.

Əgər $U = {3}$ olarsa, ən yaxın ortaq əcdad 3-dür. Əgər $U = {4}$ olarsa, ən yaxın ortaq əcdad 4-dür. Əgər $U = {3, 4}$ olarsa, ən yaxın ortaq əcdad 2-dir, çünki hər iki yolun üzərində yalnız 1 və 2 təpələri yerləşir və 2 təpəsi 1 təpəsindən 1-ə nisbətən daha uzaqdadır.

Bütün qiymətləri topladıqda: $1 dot 8 + 2 dot 4 + 3 + 4 + 2 = 25$ alırıq.
]
  ),
)

#table(
  columns: (auto, auto, 1fr),
  [*Giriş*], [*Çıxış*], [*İzah*],
  ..examples.map(
    example => (text(example.at(0), font: "Cascadia Code"), text(example.at(1), font: "Cascadia Code"), example.at(2)) 
  ).flatten()
)


== Qiymətləndirmə

Bu məsələ aşağıdakı kimi 5 alt tapşırıqdan ibarətdir:

#table(
  align: center,
  columns: (auto, 1fr, 1fr),
  [*Alt tapşırıq*], [*Əlavə məhdudiyyətlər*], [*Bal*],
  [0], [Nümunələr], [0 bal],
  [1], [$n <= 18$], [20 bal],
  [2], [$n <= 2000$], [20 bal],
  [3], [$u_i=1, v_i=i+1$], [15 bal],
  [4], [$u_i=i, v_i=i+1$], [15 bal],
  [5], [Əlavə məhdudiyyət yoxdur], [30 bal]
)