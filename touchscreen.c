#define I2C_BASE 0x13860000

static volatile unsigned int *const I2C_CON = (unsigned int *)(I2C_BASE + 0x00);
static volatile unsigned int *const I2C_STAT = (unsigned int *)(I2C_BASE + 0x04);
static volatile unsigned int *const I2C_ADD = (unsigned int *)(I2C_BASE + 0x08);
static volatile unsigned int *const I2C_DS = (unsigned int *)(I2C_BASE + 0x0C);

void touch_init(void) {
    *I2C_CON = 0xAF;
    *I2C_ADD = 0x38;
}

int touch_read(int *x, int *y) {
    if (!(*I2C_STAT & 0x1)) {
        return 0;
    }
    
    *x = (*I2C_DS & 0x0FFF);
    *y = ((*I2C_DS >> 16) & 0x0FFF);
    return 1;
}
