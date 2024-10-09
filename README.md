# Unhinged - Dating App Prototype 

Unhinged can support more than 100k members; members.txt pre-populates it with 100k members.
Each member can have dozens of attribute-value pairs -- e.g "hobby" -> "basketball".
To identify compatible members, Unhinged will translate a member's attribute-value pairs
to a list of compatible attribute-value pairs, such as "physical attribute" -> "tall".
Based on the translations, the app will rank all potential matches for a member by identifying
the people with the most amount of compatible attribute-value pairs to that member.

Due to expectations of long common prefixes, used a radix tree rather than a C++'s built-in 
map to create the map of attribute to values. This is meant to speed up the process when 
matchmaking given the users' queries.
