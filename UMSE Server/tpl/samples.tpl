<!--
   UMSE Antivirus Agent Example
   Author: David Alvarez Perez <dalvarezperez87[at]gmail[dot]com>
   Module: UMSE Intelligence Server HTML Webpage Template
   Description: This file is an UMSE intelligence server HTML webpage template.

   Copyright (c) 2019-2020. The UMSE Authors. All Rights Reserved.
   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation and/or
   other materials provided with the distribution.

   3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-->
<html>
    <head>
        <script>
            window.onkeypress = function(event) {{
               if (event.keyCode == 43) {{
                  nextPage();
               }}
               if (event.keyCode == 45) {{
                  prevPage();
               }}
            }}
            function nextPage(){{
                if(page+15<Object.keys(samples).length){{
                    clearSamplesTable();
                    page +=15;
                    fillSamplesTable();
                    updatePageNumber();
                }}
            }}
            function prevPage(){{
                if(page-15>=0){{
                    clearSamplesTable();
                    page -=15;
                    fillSamplesTable();
                    updatePageNumber();
                }}
            }}
            function updatePageNumber(){{
                document.getElementById("page").innerHTML = "Page " + (page/15+1) + " of " + Math.ceil(Object.keys(samples).length/15) + ": "
            }}
        </script>
    </head>
    <body>
        <div style="text-align:center">
            <h1>Universal Malware Sample Encryption</h1>
            <a>Malware Analyst Intelligence Console</a>
        </div>
        <br/>
        <table id="samplesTable" style="width:70%"></table>
        <hr color="lightblue" align="left" width="70%" size="3" />
        <a href="javascript:prevPage()" id="btn_prev">Prev(-)</a>
        <span id="page"></span>
        <a href="javascript:nextPage()" id="btn_next">Next(+)</a>
        <br/>
        <br/>
        <br/>
        <div id="div_search">
        <table bordercolor="lightblue" border="1" style="width:70%;border-collapse:collapse;">
            <tr>
                <td>
                    Quick sample search: <input type="text" id="input_search" />
                </td>
            </tr>
            <tr>
                <td>
                    <a id="search_results"></a>
                </td>
            </tr>
        </table>
        <div>
        <script>
            var samples = **SAMPLES_JSON_HERE**;
            var samplesTable = document.getElementById("samplesTable");
            var page = 0;
            function fillSamplesTable(){{
                var i = 0;
                var row = samplesTable.insertRow(i);
                row.bgColor = 'lightblue';
                var cell1 = row.insertCell(0);
                var cell2 = row.insertCell(1);
                var cell3 = row.insertCell(2);
                cell1.innerHTML = "<b>SAMPLE PLAINTEXT HASH</b>";
                cell2.innerHTML = "<b>FILENAME</b>";
                cell3.innerHTML = "<b>SAMPLE SIZE</b>";
                for (var prop in samples){{
                   i++;
                   if(i<=page) continue;
                   if(i>=page+15) break;
                   var row = samplesTable.insertRow(i-page);
                   var cell1 = row.insertCell(0);
                   var cell2 = row.insertCell(1);
                   var cell3 = row.insertCell(2);
                   cell1.innerHTML = '<a href="http://127.0.0.1:8080/download_sample?id=' + samples[prop].id + '">' + samples[prop].hash_sha256 + '</a>';
                   cell2.innerHTML = samples[prop].original_filename;
                   cell3.innerHTML = samples[prop].sample_size;
                   if(i==15) break;
                }}
            }}
            fillSamplesTable();
            updatePageNumber();
            function clearSamplesTable(){{
                while(document.getElementById("samplesTable").getElementsByTagName("tr").length>0){{
                    document.getElementById("samplesTable").deleteRow(0);
                }}
            }}

            var node = document.getElementById("input_search");
            node.addEventListener("keyup", function(event) {{
                document.getElementById("search_results").innerHTML = ""
                for (var prop in samples){{
                    if(document.getElementById("search_results").innerHTML.length>1000) break;
                    if(samples[prop].hash_sha256.toUpperCase().startsWith(node.value.toUpperCase()) || samples[prop].original_filename.toUpperCase().startsWith(node.value.toUpperCase())){{
                        document.getElementById("search_results").innerHTML += '<br/><a href="http://127.0.0.1:8080/download_sample?id=' + samples[prop].id + '">' + samples[prop].hash_sha256 + '</a> ' + samples[prop].original_filename;
                    }}
                }}
            }});
        </script>
    </body>
</html>