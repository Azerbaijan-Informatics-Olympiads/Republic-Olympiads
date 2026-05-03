// ready

//senior only
#import "/templateDay1-AZ.typ": *

#show: project.with(
  title: "Birləşən Krallıqlar",
  time_limit: 1,
  memory_limit: 512
)

#image("/tahir/mergin_kingdoms.png")
Rowland adlı qəribə kainatda bir sıra boyunca yerləşmiş $n$ krallıq var. $i$-ci krallığın güc səviyyəsi $a_i$ tam ədədi ilə ifadə olunur.
 
Əgər iki qonşu krallığın gücü çox fərqlənərsə, onların arasında münaqişə yarana bilər. Krallıqlar sırası o zaman *sabit* adlanır ki, hər bir iki qonşu krallığın gücü bir-birinə yaxın olsun. Daha dəqiq desək,

#align(center)[$|a_i - a_(i+1)| <= 1 $ şərti, hər bir i  $(1 <= i < n)$ üçün ödənilməlidir.]
Siz bu diyarın hökmdarı olaraq krallıqlar arasında sabitliyi qorumaq istəyirsiniz. Bunu etmək üçün siz bir əməliyyatla iki qonşu krallığı bir yeni krallıq altında birləşdirə bilirsiniz.

Güc səviyyələri $a_i$ və $a_(i+1)$ olan iki krallıq birləşəndə, siz yeni krallığın güc səviyyəsi olan bir tam ədəd $x$ seçirsiniz. Lakin yeni krallığın güc səviyyəsi birləşdirilən iki krallığın güc səviyyələri arasında olmalıdır. Yəni,
$
min(a_i, a_(i+1)) <= x <= max(a_i, a_(i+1)).
$

_Qeyd edək ki, hər əməliyyatdan sonra krallıqların sayı $1$ vahid azalır_.

Krallıqlar sırasını *sabit* etmək üçün lazım olan *minimum* əməliyyat sayını tapın.

== Giriş

Girişin birinci sətrində bir tam ədəd $n$ ($1 <= n <= 5000$) — krallıqların sayı verilir.

İkinci sətirdə $n$ tam ədəd $a_1, a_2, ..., a_n$ ($1 <= a_i <= n$) — krallıqların güc səviyyələri verilir.

== Çıxış

Bir tam ədəd — krallıqlar sırasını sabit etmək üçün lazım olan minimum əməliyyat sayını çıxışa verin.

== Məhdudiyyətlər

- $1 <= n <= 5000$
- $1 <= a_i <= n$
- alt tapşırıqlar üçün qiymətləndirmə bölməsinə baxın.

== Nümunələr

// Input, Output, Explanation
#let examples = (
  (
  "8
7 3 1 5 4 5 4 8
",
  
  "3",

[Hər əməliyyatdan əvvəl sıra belə görünür:

[#underline[*7, 3*], 1, 5, 4, 5, 4, 8]

[#text(fill: red)[3], *#underline[1, 5]*, 4, 5, 4, 8]

[3, #text(fill: red)[3], 4, 5, *#underline[4, 8]*]

[3, 3, 4, 5, #text(fill: red)[4]]  #h(2em)  ---   _bu sıra sabitdir_.
]
  ),
  (
  "3
2 1 3
",
  
  "1",

[Gücləri $1$ və $3$ olan krallıqları birləşdirib gücü 1, 2, və ya 3 olan krallıq yaratmaq olar. Nəticədə alınan sıraların hər biri sabitdir.]
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

Bu məsələ aşağıdakı kimi $7$ alt tapşırıqdan ibarətdir:

#table(
  align: center,
  columns: (auto, 1fr, 1fr),
  [*Alt tapşırıq*], [*Əlavə məhdudiyyətlər*], [*Bal*],
  [0], [Nümunələr], [0 bal],
  [1], [$n <= 6$], [5 bal],
  [2], [$n <= 10$], [5 bal],
  [3], [$n <= 20$], [13 bal],
  [4], [$a_i <= 3$, hər bir $1 <= i <= n$ üçün], [17 bal],
  [5], [$n <= 500$], [15 bal],
  [6], [$n <= 1000$], [30 bal],
  [7], [Əlavə məhdudiyyət yoxdur], [15 bal]
)