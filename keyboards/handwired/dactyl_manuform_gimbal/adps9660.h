#pragma once

int adps9660_id(uint8_t *id);

int adps9660_init(void);

int adps9660_proximity(uint8_t *data);

int adps9660_sleep(void);

int adps9660_wake(void);
