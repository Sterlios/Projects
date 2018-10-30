The Main goals of the task are:
1. an overall architecture of app (OOP is required);
2. threads communication design;
3. how code is readable, code style;
4. supposed strategy of error handling;
5. testing.

Implementation: only C++ 98/11 and STL without any additional libraries.

Create an application which calculates prime numbers for intervals:
    - Load intervals from specified xml-based file;
    - For each interval start standalone thread for calculating prime numbers;
    - Each calculation thread must store every calculated prime number to shared container (list, vector, etc);
    - Save unique prime numbers to xml-based file (primes tag).

Example of source xml file:
<root>
 <intervals>
   <interval>
     <low> 100 </low>
     <high> 200</high>
   </interval>
   <interval>
      <low> 500</low>
      <high> 888</high>
    </interval>
	....
  </intervals>
</root>
