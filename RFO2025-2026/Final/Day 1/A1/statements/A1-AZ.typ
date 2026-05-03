//  ready

#import "/templateDay1-AZ.typ": *

#show: project.with(
  title: "Mürəkkəb Şifrə",
  time_limit: 0.5,
  memory_limit: 256
)

Rəqəmlərdən və ulduz (`*`) işarələrindən ibarət şifrə şablonunuz var. Keçərli bir şifrə yaratmaq üçün hər bir `*` işarəsini tək bir rəqəmlə ($0$-dan $9$-a qədər) əvəz etməlisiniz. 

Şifrə iki qaydaya cavab verərsə, keçərli sayılır:
+ O, *mürəkkəb ədəd* olmalıdır (yəni $1$-dən ciddi böyük olan və sadə olmayan müsbət tam ədəd).
+ Onun əvvəlində əhəmiyyətsiz sıfırlar olmamalıdır (məsələn, 015 keçərli deyil).

Şablona uyğun gələn istənilən keçərli şifrəni tapın. Əgər belə bir şifrə yaratmaq mümkün deyilsə, $-1$ çap edin.


== Giriş

Girişin ilk və yeganə sətrində şifrə şablonunu təmsil edən tək bir $s$ sətri ($1 <= |s| <= 9$) verilir. $s$ sətrindəki simvolların hər biri ya rəqəm, ya da `*` işarəsidir.

Zəmanət verilir ki, bütün `*` simvollarını elə rəqəmlərlə əvəzləmək mümkündür ki, nəticədə alınan ədəddə əhəmiyyətsiz sıfırlar olmasın.

== Çıxış

Şablona uyğun gələn istənilən keçərli mürəkkəb ədədi çap edin. Əgər belə bir ədəd yoxdursa, $-1$ çap edin.

== Məhdudiyyətlər
- $1 <= |s| <= 9$, burada $|s|$, $s$ sətrinin uzunluğunu ifadə edir.

== Nümunələr

// Input, Output, Explanation
#let examples = (
  (
  "*10",
  
  "110",
  
  [Ulduz işarəsini sıfırdan başqa istənilən rəqəmlə əvəz etmək olar, çünki nəticədə alınan ədəd istənilən halda 10-a bölünəcək.]
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

Bu məsələdə 50 test var və hər testə görə 2 bal verilir.

Nümunədə verilmiş test də bu 50 testə daxildir.

Əlavə olaraq, testlərin ən az $20%$-də şifrə şablonu `*` simvolu ilə bitir, testlərin ən az $20%$-də `*` simvolu yoxdur və testlərin ən az $20%$-də şifrə şablonu 2 simvoldan ibarətdir.