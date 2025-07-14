/* if head of the list is matched with the Element. */

membership(Element, [Element|_]).
/*             OR
 * membership(Element, [Head|_]) :-
 *     Element == Head.
*/

/* recursively check in tail part if there exist Element or not. */

membership(Element, [_|Tail]) :-
    membership(Element, Tail).
