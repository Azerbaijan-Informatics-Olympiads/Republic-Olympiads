// The project function defines how your document looks.
// It takes your content and some metadata and formats it.
// Go ahead and customize it to your liking!
#let project(title: "", time_limit: 0, memory_limit: 0, body) = {
  // Set the document's basic properties.
  set document(title: title)

  set page(numbering: "1", number-align: center, header: grid(columns: (1fr, auto), [Республиканская олимпиада по информатике – Финальный тур, 2-ой день], [02 мая 2026])
  )

  set text(font: "Libertinus Serif", lang: "ru", hyphenate: false, size: 11pt)

  // Title row.
  align(center)[
    #block(text(weight: 700, 1.75em, title))
  ]

  if time_limit > 0 {
   align(center)[
      _Ограничение по времени: #time_limit сек._
    ]
  }
  
  if memory_limit > 0 {
    v(-5pt)
    align(center)[
      _Ограничение по памяти: #memory_limit mb._
    ]
  }

  // Main body.
  set par(justify: true)

  
  set list(
    indent: 1em,
    body-indent: 0.5em
  )

  set enum(
    indent: 1em,
    body-indent: 0.5em
  )
  
  body
}