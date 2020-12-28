# Universal Malware Sample Encryption (UMSE)

UMSE is a rich malware sample format. It can represent: software threats, hardware threats, the mixing of both and takes into
account very important forgotten aspects like: potential malicious elements context, life cycle and variety of nature of the elements (not limited to files) and some other things which finally improve the sample quality acquisition, storage and transport
positively impacting all subsequent reverse engineering tasks and users confidentiality.

## UMSE documentation

LaTeX: [Master Thesis (LaTeX version)](Master%20Thesis/)  
PDF: [Master Thesis (PDF version)](Master%20Thesis/thesis.pdf).

## UMSE format specification

UMSE structure [(available here)](UMSE%20format%20specification/umse.ksy) is formally specified using [Kaitai Struct](https://kaitai.io/) language.  
For practical purposes a [SweetScap 010Editor](https://www.sweetscape.com/010editor/) template [(available here)](UMSE%20format%20specification/UMSE.bt) was also developed.

## UMSE implementation

A C/C++ library [(available here)](UMSE%20Implementation) was developed to work more easily with UMSE. As most of security products are developed in C/C++, the UMSE library was developed in these languages but note that it can be used with independence of the programming language.  
A "libUmse.cbp" [Code::Blocks](http://www.codeblocks.org/) project file is available and ready to use.

## Getting started with UMSE

1. Before starting to work with UMSE it is highly recommended to read the [documentation](Master%20Thesis/)  

2. Clone the repository:
```bash
git clone https://github.com/dalvarezperez/umse.git
```

3. Start to generate your own UMSE malware samples using [UMSE tool for single malware analysts](UMSE%20tool%20for%20single%20malware%20analysts). A [Windows x64 precompiled binary](UMSE%20tool%20for%20single%20malware%20analysts/precompiled/Windows-x64.zip) is also available. Note that this tool is extremly simple and dont care about encryption anyway.    

## UMSE for antivirus companies and products

1. Develop your own [UMSE dynamic link library](UMSE%20Implementation) features.  
2. [Antivirus agent UMSE integration demostration](UMSE%20Agent).  
3. [Intelligence server integration demostration](UMSE%20Server).  
4. [Malware analyst console demostration](UMSE%20Shell).  

## Awards

1. CyberSec@GAL: [Premios cátedra R en ciberseguridade UVIGO-UDC, 2020](https://catedrarciberseguridade.com/downloads/2020-Acta_II_PREMIOS_CATEDRA_R_EN_CIBERSEGURIDAD.pdf)

## UMSE authors and contributors

1. Authors  
[David Álvarez Pérez](https://www.linkedin.com/in/davidalvarezperez/) <dalvarezperez87[at]gmail[dot]com>  
[Manuel Fernandez Veiga](https://www.researchgate.net/profile/Manuel_Fernandez-Veiga) <manuel.veiga[at]det[dot]uvigo[dot]es>  

2. Contributors.  
[How to contribute](CONTRIBUTING.md)
