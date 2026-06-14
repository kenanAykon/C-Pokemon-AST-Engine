# Pokemon Go Search Query Parser

This is a custom search query parser written in C. It mimics the search bar functionality found in Pokemon Go, allowing users to filter Pokemon data using complex logical queries.

Instead of basic string matching, this project uses **Flex** and **Bison** to build a real parser. It tokenizes the input, creates an Abstract Syntax Tree (AST), and evaluates the data according to the given rules.

## Features
* **AST-Based Evaluation:** Builds a syntax tree to handle nested queries and operator precedence.
* **Logical Operators:** Supports AND (`&`), OR (`,`), and NOT (`!`), including parentheses `()` for grouping.
* **Supported Filters:**
  * Range queries: `cp10-1500`, `hp100-`, `year2023`, `age0-5`
  * IV checks: `3*`, `4*`
  * Flags: `shiny`, `shadow`, `legendary`
  * Move matching: `@bite`

## Tech Stack
* **Language:** C
* **Tools:** Flex (Lexical Analyzer), Bison/Yacc (Parser Generator)
* 
 ##  Acknowledgments & Academic Context
This project was developed as part of an academic assignment. The data structures and data loading utilities (`pogo_types.h`, `data_loader.c/h`) were provided by the instructor as a base template. My core contribution and the main focus of this repository is the design and implementation of the **Query Parser and AST Evaluation Engine** (`lexer.l`, `parser.y`, `ast.c`).

---

# 🇹🇷 Türkçe (Turkish Version)

## Pokemon Go Arama Motoru Ayrıştırıcısı (Parser)

Bu proje, C dilinde yazılmış özel bir arama sorgusu ayrıştırıcısıdır. Pokemon Go oyunundaki arama çubuğu mekaniğini taklit ederek, karmaşık mantıksal sorgularla Pokemon verilerini filtrelemeyi sağlar.

Basit metin eşleştirme algoritmaları yerine, bu projede gerçek bir ayrıştırıcı mimarisi oluşturmak için **Flex** ve **Bison** araçları kullanılmıştır. Sistem, kullanıcı girdisini analiz eder (tokenize), hiyerarşik bir Soyut Sözdizimi Ağacı (AST) oluşturur ve envanter verilerini bu kurallara göre dinamik olarak değerlendirir.

### Özellikler
* **AST Tabanlı Değerlendirme:** İç içe geçmiş sorguları ve işlem önceliğini (operator precedence) yönetmek için soyut sözdizimi ağacı inşa eder.
* **Mantıksal Operatörler:** Gruplama için parantezler `()` dahil olmak üzere AND (`&`), OR (`,`) ve NOT (`!`) mantıksal operatörlerini destekler.
* **Desteklenen Filtreler:**
  * Aralık sorguları: `cp10-1500`, `hp100-`, `year2023`, `age0-5`
  * IV (Bireysel Değer) kontrolleri: `3*`, `4*`
  * Özel durum (boolean) bayrakları: `shiny`, `shadow`, `legendary`
  * Saldırı (Move) eşleştirme: `@bite`

### Teknoloji Yığını
* **Programlama Dili:** C
* **Araçlar:** Flex (Sözcüksel Analiz - Lexer), Bison/Yacc (Sözdizimsel Analiz - Parser)

##  Akademik Bağlam ve Katkı Beyanı
Bu proje akademik bir görevin parçası olarak geliştirilmiştir. Veri yapıları ve veritabanı okuma araçları (`pogo_types.h`, `data_loader.c/h`) eğitmen tarafından temel bir şablon olarak sağlanmıştır. Benim bu projedeki temel katkım ve bu deponun (repository) asıl odak noktası; **Sorgu Ayrıştırıcı (Query Parser) ve AST Değerlendirme Motorunun** (`lexer.l`, `parser.y`, `ast.c`) sıfırdan tasarlanıp kodlanmasıdır.
