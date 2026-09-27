class Solution {
    public String reverseParentheses(String s) {
        Stack<String> stack = new Stack<>();
        StringBuilder current = new StringBuilder();

        for (char c : s.toCharArray()) {
            if (c == '(') {
                // Save the string before entering parentheses
                stack.push(current.toString());
                current.setLength(0);
            } 
            else if (c == ')') {
                // Reverse the innermost substring
                current.reverse();

                // Add it to the string before '('
                current.insert(0, stack.pop());
            } 
            else {
                current.append(c);
            }
        }

        return current.toString();
    }
}
