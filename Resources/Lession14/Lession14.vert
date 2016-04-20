attribute vec4 a_position;
void main(void)
{
    gl_Position = CC_MVPMatrix * a_position;
}
